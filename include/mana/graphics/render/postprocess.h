#pragma once
#ifndef POST_PROCESS_H
#define POST_PROCESS_H

#include "mana/core/memoryallocator.h"
//
#include <stdbool.h>

#include "mana/graphics/render/vulkanrenderer.h"
#include "mana/graphics/shaders/blitshader.h"
#include "mana/graphics/shaders/shader.h"
#include "mana/graphics/utilities/fullscreentriangle.h"

#define POST_PROCESS_TOTAL_DEPENDENCIES 2

struct BlitPostProcess {
  struct BlitShader* blit_shader;
  VkDescriptorSet descriptor_set;
  struct FullscreenTriangle* fullscreen_triangle;
};

struct PostProcess {
  VkCommandBuffer post_process_command_buffers[2];
  struct VkFramebuffer_T* post_process_framebuffers[2];
  VkRenderPass render_pass;
  VkSemaphore post_process_semaphores[2];
  VkSampler texture_sampler;

  struct VkImage_T* color_images[2];
  struct VkDeviceMemory_T* color_image_memories[2];
  struct VkImageView_T* color_image_views[2];

  bool ping_pong;

  struct BlitPostProcess* blit_post_process;
};

int post_process_init(struct PostProcess* post_process, struct GPUAPI* gpu_api);
int post_process_delete(struct PostProcess* post_process, struct GPUAPI* gpu_api);
int post_process_start(struct PostProcess* post_process, struct GPUAPI* gpu_api);
int post_process_stop(struct PostProcess* post_process, struct GPUAPI* gpu_api);

int blit_post_process_init(struct BlitPostProcess* blit_post_, struct GPUAPI* gpu_api);
void blit_post_process_delete(struct BlitPostProcess* blit_post_process, struct GPUAPI* gpu_api);
int blit_post_process_render(struct BlitPostProcess* blit_post_, struct GPUAPI* gpu_api);

#endif  // POST_PROCESS_H