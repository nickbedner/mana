#include "graphics/texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <graphics/stb_image.h>

void texture_init(struct Texture *texture, char *path) {
  // Note: Extra 0 needed to ensure end of string
  int pathLength = strlen(path);
  texture->path = malloc(pathLength + 1);
  memset(texture->path, 0, pathLength);
  strcpy(texture->path, path);

  // Todo: Extract filetype
  int typeLength = 4;
  texture->type = malloc(typeLength + 1);
  memset(texture->type, 0, typeLength + 1);
  strcpy(texture->type, ".tst");
}

void texture_delete(struct VulkanRenderer *vulkan_renderer, struct Texture *texture) {
  vkDestroySampler(vulkan_renderer->device, texture->texture_sampler, NULL);
  vkDestroyImageView(vulkan_renderer->device, texture->texture_image_view, NULL);

  vkDestroyImage(vulkan_renderer->device, texture->texture_image, NULL);
  vkFreeMemory(vulkan_renderer->device, texture->texture_image_memory, NULL);

  free(texture->path);
  free(texture->type);
}

int texture_create_image(struct VulkanRenderer *vulkan_renderer, struct Texture *texture) {
  int texWidth, texHeight, texChannels;
  stbi_uc *pixels = stbi_load(texture->path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
  VkDeviceSize imageSize = texWidth * texHeight * 4;

  if (!pixels) return -1;
  // printf("failed to load texture image!\n");

  VkBuffer stagingBuffer = {0};
  VkDeviceMemory stagingBufferMemory = {0};
  graphics_utils_create_buffer(vulkan_renderer->device, vulkan_renderer->physical_device, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingBufferMemory);

  void *data;
  vkMapMemory(vulkan_renderer->device, stagingBufferMemory, 0, imageSize, 0, &data);
  memcpy(data, pixels, imageSize);
  vkUnmapMemory(vulkan_renderer->device, stagingBufferMemory);

  stbi_image_free(pixels);

  graphics_utils_create_image(vulkan_renderer->device, vulkan_renderer->physical_device, texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &texture->texture_image, &texture->texture_image_memory);

  graphics_utils_transition_image_layout(vulkan_renderer->device, vulkan_renderer->graphics_queue, vulkan_renderer->command_pool, &texture->texture_image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  texture_copy_buffer_to_image(vulkan_renderer, &stagingBuffer, &texture->texture_image, texWidth, texHeight);
  graphics_utils_transition_image_layout(vulkan_renderer->device, vulkan_renderer->graphics_queue, vulkan_renderer->command_pool, &texture->texture_image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vkDestroyBuffer(vulkan_renderer->device, stagingBuffer, NULL);
  vkFreeMemory(vulkan_renderer->device, stagingBufferMemory, NULL);

  return 0;
}

int texture_create_sampler(struct VulkanRenderer *vulkan_renderer, struct Texture *texture) {
  VkSamplerCreateInfo samplerInfo = {0};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = 16;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  if (vkCreateSampler(vulkan_renderer->device, &samplerInfo, NULL, &texture->texture_sampler) != VK_SUCCESS) {
    return -1;
    printf("failed to create texture sampler!\n");
  }

  return 0;
}

int texture_create_texture_image_view(struct VulkanRenderer *vulkan_renderer, struct Texture *texture) {
  texture->texture_image_view = graphics_utils_create_image_view(vulkan_renderer->device, texture->texture_image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);

  return 0;

  void texture_copy_buffer_to_image(struct VulkanRenderer * vulkan_renderer, VkBuffer * buffer, VkImage * image, uint32_t width, uint32_t height) {
    VkCommandBuffer command_buffer = graphics_utils_begin_single_time_commands(vulkan_renderer->device, vulkan_renderer->command_pool);

    VkBufferImageCopy region = {0};
    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageOffset.x = 0;
    region.imageOffset.y = 0;
    region.imageOffset.z = 0;
    region.imageExtent.width = width;
    region.imageExtent.height = height;
    region.imageExtent.depth = 1;

    vkCmdCopyBufferToImage(command_buffer, *buffer, *image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    graphics_utils_end_single_time_commands(vulkan_renderer->device, vulkan_renderer->graphics_queue, vulkan_renderer->command_pool, command_buffer);
  }
