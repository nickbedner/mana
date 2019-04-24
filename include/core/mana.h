#pragma once
#ifndef MANA_H_
#define MANA_H_

//#pragma clang diagnostic warning "-Wpragma-pack"

#include "core/common.h"
#include "core/engine.h"

#define ENGINE_ERROR 1
#define WINDOW_ERROR 2

EXPORT int init();
EXPORT int new_window(int width, int height);
EXPORT void update();
EXPORT bool should_close();
EXPORT void close_window();
EXPORT void cleanup();
EXPORT void print_fps();

struct Engine engine;

#endif // MANA_H_