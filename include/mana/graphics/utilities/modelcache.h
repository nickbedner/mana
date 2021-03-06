#pragma once
#ifndef MODEL_CACHE_H
#define MODEL_CACHE_H

#include "mana/core/memoryallocator.h"
//
#include <mana/core/gpuapi.h>
#include <stdarg.h>

#include "mana/core/vulkancore.h"
#include "mana/graphics/entities/model.h"
#include "mana/graphics/graphicscommon.h"
#include "mana/graphics/render/vulkanrenderer.h"
#include "mana/graphics/shaders/shader.h"
#include "mana/graphics/utilities/collada/modelanimation.h"
#include "mana/graphics/utilities/collada/modelanimator.h"
#include "mana/graphics/utilities/collada/modelgeometry.h"
#include "mana/graphics/utilities/collada/modelskeleton.h"
#include "mana/graphics/utilities/collada/modelskinning.h"
#include "mana/graphics/utilities/mesh.h"
#include "mana/graphics/utilities/texture.h"
#include "xmlparser.h"

struct ModelCache {
  struct Map models;
};

void model_cache_init(struct ModelCache* model_cache);
void model_cache_delete(struct ModelCache* model_cache, struct GPUAPI* gpu_api);
void model_cache_add(struct ModelCache* model_cache, struct GPUAPI* gpu_api, size_t n_models, ...);
struct Model* model_cache_get(struct ModelCache* model_cache, struct GPUAPI* gpu_api, char* model_name);

#endif  // MODEL_CACHE_H