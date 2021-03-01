#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "memoryallocator.h"
//

#include "entities/entity.h"
#include "gamestate.h"

enum CharacterState {
  CHARACTER_IDLE_STATE = 0,
  CHARACTER_WALKING_STATE
};

struct Player {
  struct Entity entity;

  float character_direction;
  enum CharacterState character_state;
};

struct GameState;

int player_init(struct Player* player, struct GameState* game_state);
void player_delete(struct Player* player, void* other);
void player_update(struct Player* player, struct GameState* game_state, float delta_time);

#endif  // PLAYER_H
