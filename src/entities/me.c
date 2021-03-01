#include "entities/me.h"

int me_init(struct Me* me, struct GameState* game_state) {
  me->entity.entity_data = me;
  me->entity.delete_func = (void (*)(void*, void*))me_delete;
  me->entity.update_func = (void (*)(void*, void*, float))me_update;

  me->state = ME_IDLE_STATE;
  me->entity.position = VEC3_ZERO;
  me->entity.direction = 1.0f;

  return 0;
}

void me_delete(struct Me* me, void* other) {
}

void me_update(struct Me* me, struct GameState* game_state, float delta_time) {
}
