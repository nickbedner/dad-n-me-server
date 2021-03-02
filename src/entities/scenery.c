#include "entities/scenery.h"

int scenery_init(struct Scenery* scenery, char* texture_path, int repeat_factor) {
  scenery->entity.entity_data = scenery;
  scenery->texture_path = strdup(texture_path);
  scenery->repeat_factor = repeat_factor;
  scenery->entity.delete_func = (void (*)(void*, void*))scenery_delete;
  scenery->entity.update_func = (void (*)(void*, void*, float))scenery_update;

  scenery->entity.position = VEC3_ZERO;
  scenery->entity.direction = 1.0f;

  return 0;
}

void scenery_delete(struct Scenery* scenery, void* other) {
  free(scenery->texture_path);
}

void scenery_update(struct Scenery* scenery, struct GameState* game_state, float delta_time) {
}
