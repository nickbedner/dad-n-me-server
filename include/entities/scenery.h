#pragma once
#ifndef SCENERY_H
#define SCENERY_H

#include "memoryallocator.h"
//

#include "entities/entity.h"
#include "gamestate.h"

struct Scenery {
  struct Entity entity;
  char* texture_path;
  int repeat_factor;
  float offset
};

struct GameState;

int scenery_init(struct Scenery* scenery, char* texture_path, float scale, int repeat_factor, float offset);
void scenery_delete(struct Scenery* scenery, void* other);
void scenery_update(struct Scenery* scenery, struct GameState* game_state, float delta_time);

#endif  // SCENERY_H
