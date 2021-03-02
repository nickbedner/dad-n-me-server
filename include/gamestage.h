#pragma once
#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "memoryallocator.h"
//
#include <cstorage/cstorage.h>

#include "dadnmeserver.h"
#include "entities/entity.h"
#include "entities/me.h"

struct GameStage {
  struct ArrayList background_entities;
  struct ArrayList state_entities;
  struct ArrayList foreground_entities;
};

int game_stage_init(struct GameStage* game_stage);
void game_stage_delete(struct GameStage* game_stage);
void game_stage_update(struct GameStage* game_stage, double delta_time);

#endif  // GAME_STAGE_H
