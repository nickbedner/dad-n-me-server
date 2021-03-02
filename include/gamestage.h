#pragma once
#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "memoryallocator.h"
//
#include <cstorage/cstorage.h>
#include <xmlparser.h>

#include "dadnmeserver.h"
#include "entities/entity.h"
#include "entities/me.h"
#include "entities/scenery.h"

struct GameStage {
  struct ArrayList scenery_entities;     // Background and floor
  struct ArrayList doodad_entities;      // Things laying around
  struct ArrayList foreground_entities;  // Foreground
};

int game_stage_init(struct GameStage* game_stage);
void game_stage_delete(struct GameStage* game_stage);
void game_stage_update(struct GameStage* game_stage, double delta_time);

#endif  // GAME_STAGE_H
