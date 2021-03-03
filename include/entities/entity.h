#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "memoryallocator.h"
//
#include <ubermath/ubermath.h>

struct Entity {
  unsigned int entity_id;
  vec3 position;
  float direction;
  float width;
  float height;
  float scale;
  void* entity_data;
  void (*delete_func)(void*, void*);
  void (*update_func)(void*, void*, float);
  void (*render_func)(void*, void*);
  void (*recreate_func)(void*, void*);
};

#endif  // ENTITY_H
