/*#pragma once
#ifndef ME_H
#define ME_H

#include "memoryallocator.h"
//

#include "entities/entity.h"
#include "gamestate.h"

enum MeState {
  ME_IDLE_STATE = 0,
  ME_WALKING_STATE
};

struct Me {
  struct Entity entity;
  enum MeState state;
};

struct GameState;

int me_init(struct Me* me, struct GameState* game_state);
void me_delete(struct Me* me, void* other);
void me_update(struct Me* me, struct GameState* game_state, float delta_time);

#endif  // ME_H*/
