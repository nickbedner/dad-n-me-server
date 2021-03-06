/*#pragma once
#ifndef WILBUR_H
#define WILBUR_H

#include "memoryallocator.h"
//

#include "entities/entity.h"
#include "gamestate.h"

enum WilburState {
  WILBUR_IDLE_STATE = 0,
  WILBUR_WALKING_STATE
};

struct Wilbur {
  //struct Entity entity;
  unsigned int entity_id;
  enum WilburState state;
};

struct GameState;

int wilbur_init(struct Wilbur* wilbur, struct GameState* game_state);
void wilbur_delete(struct Wilbur* wilbur, void* other);
void wilbur_update(struct Wilbur* wilbur, struct GameState* game_state, float delta_time);

#endif  // WILBUR_H
*/