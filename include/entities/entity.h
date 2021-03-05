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

struct EntityUpdateData {
  void* entity_handle;
  void* game_handle;
  float delta_time;
};

static inline void entity_update_job(void* data) {
  struct EntityUpdateData* update_data = data;
  struct Entity* entity = update_data->entity_handle;
  (*entity->update_func)(entity->entity_data, update_data->game_handle, update_data->delta_time);
}

#endif  // ENTITY_H
