#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "memoryallocator.h"
//
#include <cstorage/cstorage.h>

#include "dadnmeserver.h"
#include "entities/entity.h"
#include "entities/me.h"

struct GameState {
  struct ArrayList entites;
};

int game_state_init(struct GameState* game_state);
void game_state_delete(struct GameState* game_state);
void game_state_update(struct GameState* game_state, double delta_time);

#endif  // GAME_STATE_H
