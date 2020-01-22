#pragma once
#ifndef GRAPHICS_UTILS_H
#define GRAPHICS_UTILS_H

#include <cglm/cglm.h>
#include <cstorage/cstorage.h>
#include <vulkan/vulkan.h>

#include "mana/graphics/graphicscommon.h"

static inline void graphics_utils_create_image_view(struct VkDevice_T *device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView *image_view);
static inline int graphics_utils_create_image(struct VkDevice_T *device, struct VkPhysicalDevice_T *physical_device, uint32_t width, uint32_t height, uint32_t mip_levels, VkSampleCountFlagBits num_samples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *image_memory);
static inline int graphics_utils_create_buffer(struct VkDevice_T *device, struct VkPhysicalDevice_T *physical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer *buffer, VkDeviceMemory *buffer_memory);
static inline int graphics_utils_transition_image_layout(struct VkDevice_T *device, struct VkQueue_T *graphics_queue, struct VkCommandPool_T *command_pool, VkImage *image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
static inline uint32_t graphics_utils_find_memory_type(struct VkPhysicalDevice_T *physical_device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
static inline VkCommandBuffer graphics_utils_begin_single_time_commands(struct VkDevice_T *device, struct VkCommandPool_T *command_pool);
static inline void graphics_utils_end_single_time_commands(struct VkDevice_T *device, struct VkQueue_T *graphics_queue, struct VkCommandPool_T *command_pool, VkCommandBuffer command_buffer);
static inline int graphics_utils_create_sampler(struct VkDevice_T *device, VkSampler *texture_sampler);

static inline void graphics_utils_create_image_view(struct VkDevice_T *device, VkImage image, VkFormat format, VkImageAspectFlags aspect_flags, VkImageView *image_view) {
  VkImageViewCreateInfo view_info = {0};
  view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  view_info.image = image;
  view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  view_info.format = format;
  view_info.subresourceRange.aspectMask = aspect_flags;
  view_info.subresourceRange.baseMipLevel = 0;
  view_info.subresourceRange.levelCount = 1;
  view_info.subresourceRange.baseArrayLayer = 0;
  view_info.subresourceRange.layerCount = 1;

  if (vkCreateImageView(device, &view_info, NULL, image_view) != VK_SUCCESS)
    fprintf(stderr, "failed to create texture image view!");
}

static inline int graphics_utils_create_image(struct VkDevice_T *device, struct VkPhysicalDevice_T *physical_device, uint32_t width, uint32_t height, uint32_t mip_levels, VkSampleCountFlagBits num_samples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage *image, VkDeviceMemory *image_memory) {
  VkImageCreateInfo image_info = {0};
  image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  image_info.imageType = VK_IMAGE_TYPE_2D;
  image_info.extent.width = width;
  image_info.extent.height = height;
  image_info.extent.depth = 1;
  image_info.mipLevels = 1;
  image_info.arrayLayers = 1;
  image_info.format = format;
  image_info.tiling = tiling;
  image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  image_info.usage = usage;
  image_info.samples = num_samples;
  image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateImage(device, &image_info, NULL, image) != VK_SUCCESS)
    return -1;
  // printf("failed to create image!");

  VkMemoryRequirements mem_mequirements;
  vkGetImageMemoryRequirements(device, *image, &mem_mequirements);

  VkMemoryAllocateInfo alloc_info = {0};
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize = mem_mequirements.size;
  alloc_info.memoryTypeIndex = graphics_utils_find_memory_type(physical_device, mem_mequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(device, &alloc_info, NULL, image_memory) !=
      VK_SUCCESS)
    return -1;
  // printf("failed to allocate image memory!");

  vkBindImageMemory(device, *image, *image_memory, 0);

  return 0;
}

static inline int graphics_utils_create_buffer(struct VkDevice_T *device, struct VkPhysicalDevice_T *physical_device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer *buffer, VkDeviceMemory *buffer_memory) {
  VkBufferCreateInfo buffer_info = {0};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = size;
  buffer_info.usage = usage;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(device, &buffer_info, NULL, buffer) != VK_SUCCESS) {
    return -1;
    fprintf(stderr, "failed to create buffer!\n");
  }

  VkMemoryRequirements mem_requirements;
  vkGetBufferMemoryRequirements(device, *buffer, &mem_requirements);

  VkMemoryAllocateInfo alloc_info = {0};
  alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  alloc_info.allocationSize = mem_requirements.size;
  alloc_info.memoryTypeIndex = graphics_utils_find_memory_type(physical_device, mem_requirements.memoryTypeBits, properties);

  if (vkAllocateMemory(device, &alloc_info, NULL, buffer_memory) != VK_SUCCESS) {
    return -1;
    fprintf(stderr, "failed to allocate buffer memory!\n");
  }

  vkBindBufferMemory(device, *buffer, *buffer_memory, 0);

  return 0;
}

static inline int graphics_utils_transition_image_layout(struct VkDevice_T *device, struct VkQueue_T *graphics_queue, struct VkCommandPool_T *command_pool, VkImage *image, VkFormat format, VkImageLayout old_layout, VkImageLayout new_layout) {
  VkCommandBuffer commandBuffer = graphics_utils_begin_single_time_commands(device, command_pool);

  VkImageMemoryBarrier barrier = {0};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = old_layout;
  barrier.newLayout = new_layout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = *image;

  if (new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    if (format == VK_FORMAT_D32_SFLOAT_S8_UINT ||
        format == VK_FORMAT_D24_UNORM_S8_UINT)
      barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
  } else
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags source_stage = {0};
  VkPipelineStageFlags destination_stage = {0};

  if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED &&
      new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destination_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  } else {
    fprintf(stderr, "unsupported layout transition!");
    return -1;
  }

  vkCmdPipelineBarrier(commandBuffer, source_stage, destination_stage, 0, 0, NULL, 0, NULL, 1, &barrier);

  graphics_utils_end_single_time_commands(device, graphics_queue, command_pool, commandBuffer);

  return 0;
}

static inline uint32_t graphics_utils_find_memory_type(struct VkPhysicalDevice_T *physical_device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties mem_properties;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_properties);

  for (uint32_t i = 0; i < mem_properties.memoryTypeCount; i++)
    if ((typeFilter & (1 << i)) && (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
      return i;

  printf("failed to find suitable memory type!\n");

  return -1;
}

static inline VkCommandBuffer graphics_utils_begin_single_time_commands(struct VkDevice_T *device, struct VkCommandPool_T *command_pool) {
  VkCommandBufferAllocateInfo allocInfo = {0};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = command_pool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(device, &allocInfo, &command_buffer);

  VkCommandBufferBeginInfo begin_info = {0};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &begin_info);

  return command_buffer;
}

static inline void graphics_utils_end_single_time_commands(struct VkDevice_T *device, struct VkQueue_T *graphics_queue, struct VkCommandPool_T *command_pool, VkCommandBuffer command_buffer) {
  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submit_info = {0};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command_buffer;

  vkQueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
  vkQueueWaitIdle(graphics_queue);

  vkFreeCommandBuffers(device, command_pool, 1, &command_buffer);
}

static inline int graphics_utils_create_sampler(struct VkDevice_T *device, VkSampler *texture_sampler) {
  VkSamplerCreateInfo sampler_info = {0};
  sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  sampler_info.magFilter = VK_FILTER_LINEAR;
  sampler_info.minFilter = VK_FILTER_LINEAR;
  sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  sampler_info.anisotropyEnable = VK_TRUE;
  sampler_info.maxAnisotropy = 16;
  sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  sampler_info.unnormalizedCoordinates = VK_FALSE;
  sampler_info.compareEnable = VK_FALSE;
  sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  if (vkCreateSampler(device, &sampler_info, NULL, texture_sampler) != VK_SUCCESS) {
    return -1;
    printf("failed to create texture sampler!\n");
  }

  return 0;
}

#endif  // GRAPHICS_UTILS_H
