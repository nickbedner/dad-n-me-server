#pragma once
#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include "memoryallocator.h"
//
#include <cstorage/cstorage.h>
#include <xmlparser.h>

#include "dadnmeserver.h"

struct GameStage {
};

int game_stage_init(struct GameStage* game_stage);
void game_stage_delete(struct GameStage* game_stage);

#endif  // GAME_STAGE_H
