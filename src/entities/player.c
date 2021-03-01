#include "entities/player.h"

int player_init(struct Player* player, struct GameState* game_state) {
  player->entity.entity_data = player;
  player->entity.delete_func = (void (*)(void*, void*))player_delete;
  player->entity.update_func = (void (*)(void*, void*, float))player_update;

  player->character_state = CHARACTER_IDLE_STATE;
  player->entity.position = VEC3_ZERO;
  player->character_direction = 1.0f;

  return 0;
}

void player_delete(struct Player* player, void* other) {
}

void player_update(struct Player* player, struct GameState* game_state, float delta_time) {
}
