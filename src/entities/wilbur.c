#include "entities/wilbur.h"

int wilbur_init(struct Wilbur* wilbur, struct GameState* game_state) {
  wilbur->entity.entity_data = wilbur;
  wilbur->entity.delete_func = (void (*)(void*, void*))wilbur_delete;
  wilbur->entity.update_func = (void (*)(void*, void*, float))wilbur_update;

  wilbur->state = WILBUR_IDLE_STATE;
  wilbur->entity.position = VEC3_ZERO;
  wilbur->entity.direction = 1.0f;

  return 0;
}

void wilbur_delete(struct Wilbur* wilbur, void* other) {
}

void wilbur_update(struct Wilbur* wilbur, struct GameState* game_state, float delta_time) {
}
