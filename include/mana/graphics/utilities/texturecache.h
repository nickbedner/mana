#pragma once
#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <mana/core/memoryallocator.h>
//
#include <cstorage/cstorage.h>
#include <stdarg.h>

#include "mana/graphics/utilities/texture.h"

struct TextureCache {
  struct Map textures;
};

void texture_cache_init(struct TextureCache* texture_cache, struct GPUAPI* gpu_api, size_t n_textures, ...);
void texture_cache_delete(struct TextureCache* texture_cache, struct GPUAPI* gpu_api);
struct Texture* texture_cache_get(struct TextureCache* texture_cache, char* texture_name);

#endif  // TEXTURE_CACHE_H