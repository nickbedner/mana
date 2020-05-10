#include "mana/graphics/render/swapchain.h"

int swap_chain_init(struct SwapChain* swap_chain, struct VulkanState* vulkan_renderer, int width, int height) {
  // TODO: Load this from options and maybe move later
  swap_chain->supersample_scale = 1.0f;
  swap_chain->current_frame = 0;
  struct SwapChainSupportDetails swap_chain_support = {{0}};

  vector_init(&swap_chain_support.formats, sizeof(struct VkSurfaceFormatKHR));
  vector_init(&swap_chain_support.present_modes, sizeof(enum VkPresentModeKHR));

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan_renderer->physical_device, vulkan_renderer->surface, &swap_chain_support.capabilities);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_renderer->physical_device, vulkan_renderer->surface, &format_count, NULL);

  if (format_count != 0) {
    vector_resize(&swap_chain_support.formats, format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_renderer->physical_device, vulkan_renderer->surface, &format_count, swap_chain_support.formats.items);
    swap_chain_support.formats.size = format_count;
  }

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_renderer->physical_device, vulkan_renderer->surface, &present_mode_count, NULL);

  if (present_mode_count != 0) {
    vector_resize(&swap_chain_support.present_modes, present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_renderer->physical_device, vulkan_renderer->surface, &present_mode_count, swap_chain_support.present_modes.items);
    swap_chain_support.present_modes.size = present_mode_count;
  }

  VkSurfaceFormatKHR surface_format = {0};

  if (format_count == 1 && ((struct VkSurfaceFormatKHR*)vector_get(&swap_chain_support.formats, 0))->format == VK_FORMAT_UNDEFINED) {
    surface_format.format = VK_FORMAT_B8G8R8A8_UNORM;
    surface_format.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  } else {
    for (int swap_chain_format_num = 0; swap_chain_format_num < vector_size(&swap_chain_support.formats); swap_chain_format_num++) {
      if (((struct VkSurfaceFormatKHR*)vector_get(&swap_chain_support.formats, swap_chain_format_num))->format == VK_FORMAT_B8G8R8A8_UNORM && ((struct VkSurfaceFormatKHR*)vector_get(&swap_chain_support.formats, swap_chain_format_num))->colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        surface_format = *(struct VkSurfaceFormatKHR*)vector_get(&swap_chain_support.formats, swap_chain_format_num);
        break;
      } else
        surface_format = *(struct VkSurfaceFormatKHR*)vector_get(&swap_chain_support.formats, 0);
    }
  }

  // Testing 10 bit swapchain output
  // Seems to work on Nvidia Studio Driver
  // TODO: if 10_bit_enabled
  //surface_format.format = VK_FORMAT_A2B10G10R10_UNORM_PACK32;

  VkPresentModeKHR present_mode = {0};

  for (int swap_chain_present_num = 0; swap_chain_present_num < vector_size(&swap_chain_support.present_modes); swap_chain_present_num++) {
    if ((enum VkPresentModeKHR)vector_get(&swap_chain_support.present_modes, swap_chain_present_num) == VK_PRESENT_MODE_MAILBOX_KHR) {
      present_mode = (enum VkPresentModeKHR)vector_get(&swap_chain_support.present_modes, swap_chain_present_num);
      break;
    } else if ((enum VkPresentModeKHR)vector_get(&swap_chain_support.present_modes, swap_chain_present_num) == VK_PRESENT_MODE_IMMEDIATE_KHR)
      present_mode = (enum VkPresentModeKHR)vector_get(&swap_chain_support.present_modes, swap_chain_present_num);
  }

  // Force Vsync
  // TODO: if vsync_enabled
  present_mode = VK_PRESENT_MODE_FIFO_KHR;

  VkExtent2D extent = {width, height};
  if (swap_chain_support.capabilities.currentExtent.width != UINT32_MAX)
    extent = swap_chain_support.capabilities.currentExtent;
  else {
    extent.width = MAX(swap_chain_support.capabilities.minImageExtent.width, MIN(swap_chain_support.capabilities.maxImageExtent.width, extent.width));
    extent.height = MAX(swap_chain_support.capabilities.minImageExtent.height, MIN(swap_chain_support.capabilities.maxImageExtent.height, extent.height));
  }

  uint32_t image_count = swap_chain_support.capabilities.minImageCount + 1;
  if (swap_chain_support.capabilities.maxImageCount > 0 && image_count > swap_chain_support.capabilities.maxImageCount)
    image_count = swap_chain_support.capabilities.maxImageCount;

  VkSwapchainCreateInfoKHR swapchain_info = {0};
  swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapchain_info.surface = vulkan_renderer->surface;

  swapchain_info.minImageCount = image_count;
  swapchain_info.imageFormat = surface_format.format;
  swapchain_info.imageColorSpace = surface_format.colorSpace;
  swapchain_info.imageExtent = extent;
  swapchain_info.imageArrayLayers = 1;
  swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  uint32_t queue_family_indices[] = {(&vulkan_renderer->indices)->graphics_family, (&vulkan_renderer->indices)->present_family};

  if ((&vulkan_renderer->indices)->graphics_family != (&vulkan_renderer->indices)->present_family) {
    swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapchain_info.queueFamilyIndexCount = 2;
    swapchain_info.pQueueFamilyIndices = queue_family_indices;
  } else
    swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

  swapchain_info.preTransform = swap_chain_support.capabilities.currentTransform;
  swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapchain_info.presentMode = present_mode;
  swapchain_info.clipped = VK_TRUE;

  if (vkCreateSwapchainKHR(vulkan_renderer->device, &swapchain_info, NULL, &swap_chain->swap_chain_khr) != VK_SUCCESS)
    return VULKAN_RENDERER_CREATE_SWAP_CHAIN_ERROR;

  vkGetSwapchainImagesKHR(vulkan_renderer->device, swap_chain->swap_chain_khr, &image_count, NULL);
  vkGetSwapchainImagesKHR(vulkan_renderer->device, swap_chain->swap_chain_khr, &image_count, swap_chain->swap_chain_images);

  swap_chain->swap_chain_image_format = surface_format.format;
  swap_chain->swap_chain_extent = extent;

  vector_delete(&swap_chain_support.formats);
  vector_delete(&swap_chain_support.present_modes);
  ////////////////////////////////////////////////////////

  // TODO: Clean this up like GBuffer
  for (size_t i = 0; i < MAX_SWAP_CHAIN_FRAMES; i++) {
    VkImageViewCreateInfo view_info = {0};
    view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.image = swap_chain->swap_chain_images[i];
    view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_info.format = vulkan_renderer->swap_chain->swap_chain_image_format;
    view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    view_info.subresourceRange.baseMipLevel = 0;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.baseArrayLayer = 0;
    view_info.subresourceRange.layerCount = 1;

    if (vkCreateImageView(vulkan_renderer->device, &view_info, NULL, &swap_chain->swap_chain_image_views[i]) != VK_SUCCESS)
      return VULKAN_RENDERER_CREATE_IMAGE_VIEWS_ERROR;
  }

  struct VkAttachmentDescription color_attachment = {0};
  graphics_utils_create_color_attachment(vulkan_renderer->swap_chain->swap_chain_image_format, &color_attachment);
  color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;

  VkAttachmentReference color_attachment_ref = {0};
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  struct VkAttachmentReference color_attachment_references = color_attachment_ref;
  VkSubpassDescription subpass = {0};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &color_attachment_references;

  VkSubpassDependency dependency = {0};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  VkRenderPassCreateInfo render_pass_info = {0};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  render_pass_info.attachmentCount = 1;
  render_pass_info.pAttachments = &color_attachment;
  render_pass_info.subpassCount = 1;
  render_pass_info.pSubpasses = &subpass;
  render_pass_info.dependencyCount = 1;
  render_pass_info.pDependencies = &dependency;

  if (vkCreateRenderPass(vulkan_renderer->device, &render_pass_info, NULL, &swap_chain->render_pass) != VK_SUCCESS)
    return 0;

  for (int loop_num = 0; loop_num < MAX_SWAP_CHAIN_FRAMES; loop_num++) {
    VkFramebufferCreateInfo framebuffer_info = {0};
    framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_info.renderPass = vulkan_renderer->swap_chain->render_pass;
    framebuffer_info.attachmentCount = 1;
    framebuffer_info.pAttachments = &swap_chain->swap_chain_image_views[loop_num];
    framebuffer_info.width = vulkan_renderer->swap_chain->swap_chain_extent.width;
    framebuffer_info.height = vulkan_renderer->swap_chain->swap_chain_extent.height;
    framebuffer_info.layers = 1;

    if (vkCreateFramebuffer(vulkan_renderer->device, &framebuffer_info, NULL, &swap_chain->swap_chain_framebuffers[loop_num]) != VK_SUCCESS)
      return VULKAN_RENDERER_CREATE_FRAME_BUFFER_ERROR;
  }

  // Swapchain command buffer
  VkCommandBufferAllocateInfo alloc_info_swapchain = {0};
  alloc_info_swapchain.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  alloc_info_swapchain.commandPool = vulkan_renderer->command_pool;
  alloc_info_swapchain.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  alloc_info_swapchain.commandBufferCount = (uint32_t)MAX_SWAP_CHAIN_FRAMES;

  if (vkAllocateCommandBuffers(vulkan_renderer->device, &alloc_info_swapchain, swap_chain->swap_chain_command_buffers) != VK_SUCCESS)
    return VULKAN_RENDERER_CREATE_COMMAND_BUFFER_ERROR;

  memset(swap_chain->in_flight_fences, 0, sizeof(swap_chain->in_flight_fences));

  VkSemaphoreCreateInfo semaphore_info = {0};
  semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fence_info = {0};
  fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (vkCreateSemaphore(vulkan_renderer->device, &semaphore_info, NULL, &swap_chain->image_available_semaphores[i]) != VK_SUCCESS || vkCreateSemaphore(vulkan_renderer->device, &semaphore_info, NULL, &swap_chain->render_finished_semaphores[i]) != VK_SUCCESS || vkCreateFence(vulkan_renderer->device, &fence_info, NULL, &swap_chain->in_flight_fences[i]) != VK_SUCCESS)
      return VULKAN_RENDERER_CREATE_SYNC_OBJECT_ERROR;
  }

  swap_chain->blit_swap_chain = calloc(1, sizeof(struct BlitSwapChain));

  return 1;
  //return VULKAN_RENDERER_SUCCESS;
}

void swap_chain_delete(struct SwapChain* swap_chain, struct VulkanState* vulkan_renderer) {
  blit_swap_chain_delete(swap_chain->blit_swap_chain, vulkan_renderer);
  free(swap_chain->blit_swap_chain);

  for (int loop_num = 0; loop_num < MAX_FRAMES_IN_FLIGHT; loop_num++)
    vkWaitForFences(vulkan_renderer->device, 1, &vulkan_renderer->swap_chain->in_flight_fences[loop_num], VK_TRUE, UINT64_MAX);

  vkDestroyRenderPass(vulkan_renderer->device, swap_chain->render_pass, NULL);

  for (int loop_num = 0; loop_num < MAX_SWAP_CHAIN_FRAMES; loop_num++) {
    vkDestroyFramebuffer(vulkan_renderer->device, swap_chain->swap_chain_framebuffers[loop_num], NULL);
    vkDestroyImageView(vulkan_renderer->device, swap_chain->swap_chain_image_views[loop_num], NULL);
  }

  vkDestroySwapchainKHR(vulkan_renderer->device, vulkan_renderer->swap_chain->swap_chain_khr, NULL);
  vkFreeCommandBuffers(vulkan_renderer->device, vulkan_renderer->command_pool, 3, swap_chain->swap_chain_command_buffers);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(vulkan_renderer->device, swap_chain->render_finished_semaphores[i], NULL);
    vkDestroySemaphore(vulkan_renderer->device, swap_chain->image_available_semaphores[i], NULL);
    vkDestroyFence(vulkan_renderer->device, swap_chain->in_flight_fences[i], NULL);
  }
}

int swap_chain_start(struct SwapChain* swap_chain, struct VulkanState* vulkan_renderer, int swap_chain_num) {
  VkCommandBufferBeginInfo begin_info = {0};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

  if (vkBeginCommandBuffer(swap_chain->swap_chain_command_buffers[swap_chain_num], &begin_info) != VK_SUCCESS)
    return VULKAN_RENDERER_CREATE_COMMAND_BUFFER_ERROR;

  VkRenderPassBeginInfo render_pass_info = {0};
  render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  render_pass_info.renderPass = vulkan_renderer->swap_chain->render_pass;
  render_pass_info.framebuffer = vulkan_renderer->swap_chain->swap_chain_framebuffers[swap_chain_num];
  render_pass_info.renderArea.offset.x = 0;
  render_pass_info.renderArea.offset.y = 0;
  render_pass_info.renderArea.extent = vulkan_renderer->swap_chain->swap_chain_extent;

  VkClearValue clear_value = {0};
  VkClearColorValue clear_color = {{0.0f, 0.0f, 0.0f, 0.0f}};
  clear_value.color = clear_color;

  render_pass_info.clearValueCount = 1;
  render_pass_info.pClearValues = &clear_value;

  vkCmdBeginRenderPass(swap_chain->swap_chain_command_buffers[swap_chain_num], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

  return VULKAN_RENDERER_SUCCESS;
}

int swap_chain_stop(struct SwapChain* swap_chain, struct VulkanState* vulkan_renderer, int swap_chain_num) {
  vkCmdEndRenderPass(swap_chain->swap_chain_command_buffers[swap_chain_num]);

  if (vkEndCommandBuffer(swap_chain->swap_chain_command_buffers[swap_chain_num]) != VK_SUCCESS)
    return VULKAN_RENDERER_CREATE_COMMAND_BUFFER_ERROR;

  return VULKAN_RENDERER_SUCCESS;
}

/////////////////////////////////////////////////

int blit_swap_chain_init(struct BlitSwapChain* blit_swap_chain, struct VulkanState* vulkan_renderer) {
  blit_swap_chain->blit_shader = calloc(1, sizeof(struct BlitShader));
  blit_shader_init(blit_swap_chain->blit_shader, vulkan_renderer, vulkan_renderer->swap_chain->render_pass, 2);

  struct Shader* shader = blit_swap_chain->blit_shader->shader;

  VkDescriptorSetLayout layout = {0};
  layout = shader->descriptor_set_layout;

  VkDescriptorSetAllocateInfo alloc_info = {0};
  alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  alloc_info.descriptorPool = shader->descriptor_pool;
  alloc_info.descriptorSetCount = 1;
  alloc_info.pSetLayouts = &layout;

  memset(blit_swap_chain->descriptor_sets, 0, sizeof(blit_swap_chain->descriptor_sets));

  for (int ping_pong_target = 0; ping_pong_target <= 1; ping_pong_target++) {
    if (vkAllocateDescriptorSets(vulkan_renderer->device, &alloc_info, &blit_swap_chain->descriptor_sets[ping_pong_target]) != VK_SUCCESS) {
      fprintf(stderr, "failed to allocate descriptor sets!\n");
      return 0;
    }

    VkDescriptorImageInfo image_info = {0};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = vulkan_renderer->post_process->color_image_views[ping_pong_target];
    image_info.sampler = vulkan_renderer->post_process->texture_sampler;

    VkWriteDescriptorSet dc;
    memset(&dc, 0, sizeof(dc));

    dc.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    dc.dstSet = blit_swap_chain->descriptor_sets[ping_pong_target];
    dc.dstBinding = 0;
    dc.dstArrayElement = 0;
    dc.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    dc.descriptorCount = 1;
    dc.pImageInfo = &image_info;

    vkUpdateDescriptorSets(vulkan_renderer->device, 1, &dc, 0, NULL);
  }

  blit_swap_chain->fullscreen_quad = calloc(1, sizeof(struct FullscreenQuad));
  fullscreen_quad_init(blit_swap_chain->fullscreen_quad, vulkan_renderer);

  return 1;
}

void blit_swap_chain_delete(struct BlitSwapChain* blit_swap_chain, struct VulkanState* vulkan_renderer) {
  fullscreen_quad_delete(blit_swap_chain->fullscreen_quad, vulkan_renderer);
  free(blit_swap_chain->fullscreen_quad);
  blit_shader_delete(blit_swap_chain->blit_shader, vulkan_renderer);
  free(blit_swap_chain->blit_shader);
}

void blit_swap_chain_render(struct BlitSwapChain* blit_swap_chain, struct VulkanState* vulkan_renderer) {
  for (size_t swapchain_num = 0; swapchain_num < MAX_SWAP_CHAIN_FRAMES; swapchain_num++) {
    swap_chain_start(vulkan_renderer->swap_chain, vulkan_renderer, swapchain_num);

    vkCmdBindPipeline(vulkan_renderer->swap_chain->swap_chain_command_buffers[swapchain_num], VK_PIPELINE_BIND_POINT_GRAPHICS, blit_swap_chain->blit_shader->shader->graphics_pipeline);
    VkBuffer vertex_buffers[] = {blit_swap_chain->fullscreen_quad->vertex_buffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(vulkan_renderer->swap_chain->swap_chain_command_buffers[swapchain_num], 0, 1, vertex_buffers, offsets);
    vkCmdBindIndexBuffer(vulkan_renderer->swap_chain->swap_chain_command_buffers[swapchain_num], blit_swap_chain->fullscreen_quad->index_buffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets(vulkan_renderer->swap_chain->swap_chain_command_buffers[swapchain_num], VK_PIPELINE_BIND_POINT_GRAPHICS, blit_swap_chain->blit_shader->shader->pipeline_layout, 0, 1, &blit_swap_chain->descriptor_sets[vulkan_renderer->post_process->ping_pong ^ true], 0, NULL);
    vkCmdDrawIndexed(vulkan_renderer->swap_chain->swap_chain_command_buffers[swapchain_num], blit_swap_chain->fullscreen_quad->mesh->indices->size, 1, 0, 0, 0);

    swap_chain_stop(vulkan_renderer->swap_chain, vulkan_renderer, swapchain_num);
  }
}
