/*#include "gamestate.h"

int game_state_init(struct GameState* game_state) {
  game_state->game_stage = calloc(1, sizeof(struct GameStage));
  game_stage_init(game_state->game_stage);

  return 0;
}

void game_state_delete(struct GameState* game_state) {
  game_stage_delete(game_state->game_stage);

  free(game_state->game_stage);
}

void game_state_update(struct GameState* game_state, double delta_time) {}*/