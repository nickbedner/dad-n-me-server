#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "memoryallocator.h"
//
#include <cstorage/cstorage.h>

#include "dadnmeserver.h"
#include "entities/entity.h"
#include "entities/me.h"
#include "gamestage.h"

struct GameState {
  struct GameStage game_stage;
};

int game_state_init(struct GameState* game_state);
void game_state_delete(struct GameState* game_state);
void game_state_update(struct GameState* game_state, double delta_time);

#endif  // GAME_STATE_H
