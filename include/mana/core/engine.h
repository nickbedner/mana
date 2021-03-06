#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "mana/core/memoryallocator.h"
//
#include <threads/threads.h>
#include <time.h>

#include "mana/core/gpuapi.h"
#include "mana/core/graphicslibrary.h"
#include "mana/core/vulkancore.h"
#include "mana/graphics/render/window.h"

#define MAX_GRAPHICS_LIBRARY_EXTENSIONS 32
#define FPS_COUNT 10

enum ENGINE_STATUS {
  ENGINE_SUCCESS = 0,
  ENGINE_GRAPHICS_LIBRARY_ERROR,
  ENGINE_GPU_API_ERROR,
  ENGINE_LAST_ERROR
};

struct FPSCounter {
  int fps_past[FPS_COUNT];
  double limit_update_fps;
  // maybe cap fps at 144 for limit? 30, 60, 120, 144
  double limit_draw_fps;
  int input[128];
  double now_time, last_time, delta_time, timer;
  int frames;
  double last_render_time;
  int fps;
  double target_fps;
  double average_fps;
  int updates;

  // frame safe
  double second_target_fps;
  double second_average_fps;
  int second_frames;
  int second_updates;
};

struct EngineSettings {
  enum GraphicsLibraryType graphics_library_type;
  enum APIType gpu_api_type;
};

struct Engine {
  struct EngineSettings engine_settings;
  struct FPSCounter fps_counter;
  struct GraphicsLibrary graphics_library;
  struct GPUAPI gpu_api;
};

int engine_init(struct Engine* engine, struct EngineSettings engine_settings);
void engine_delete(struct Engine* engine);
double engine_get_time();
int engine_get_max_omp_threads();

#endif  // ENGINE_H
