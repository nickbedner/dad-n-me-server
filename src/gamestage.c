#include "gamestage.h"

int game_stage_init(struct GameStage* game_stage) {
  array_list_init(&game_stage->scenery_entities);
  // Load stage from file
  // Scenery is always drawn behind
  // Doodads are drawn with depth ordering
  struct XmlNode* game_stage_node = xml_parser_load_xml_file("./assets/stages/gamestage.xml");
  struct XmlNode* scenery_node = xml_node_get_child(game_stage_node, "scenery");
  const char* scenery_list_key = NULL;
  struct MapIter scenery_list_iter = map_iter();

  struct SceneryBucket {
    struct Scenery* scenery[64];
    struct XmlNode* node[64];
  } texture_settings_bucket = {0};

  int total_scenery_num = 0;
  while ((scenery_list_key = map_next(scenery_node->child_nodes, &scenery_list_iter)))
    texture_settings_bucket.node[total_scenery_num++] = array_list_get(*((struct ArrayList**)map_get(scenery_node->child_nodes, scenery_list_key)), 0);

  //#pragma omp parallel for schedule(dynamic)
  for (int scenery_num = 0; scenery_num < total_scenery_num; scenery_num++) {
    texture_settings_bucket.scenery[scenery_num] = calloc(1, sizeof(struct Scenery));
    struct XmlNode* position_node = xml_node_get_child(texture_settings_bucket.node[scenery_num], "position");
    int repeat_factor = atoi(xml_node_get_data(xml_node_get_child(texture_settings_bucket.node[scenery_num], "repeat")));
    scenery_init(texture_settings_bucket.scenery[scenery_num], xml_node_get_attribute(position_node, "path"), repeat_factor);
    float x = atof(xml_node_get_data(xml_node_get_child(position_node, "x")));
    float y = atof(xml_node_get_data(xml_node_get_child(position_node, "y")));
    float z = atof(xml_node_get_data(xml_node_get_child(position_node, "z")));
    texture_settings_bucket.scenery[scenery_num]->entity.position = (vec3){.x = x, .y = y, .z = z};
  }

  for (int scenery_num = 0; scenery_num < total_scenery_num; scenery_num++)
    array_list_add(&game_stage->scenery_entities, texture_settings_bucket.scenery[scenery_num]);
  xml_parser_delete(game_stage_node);

  return 0;
}
void game_stage_delete(struct GameStage* game_stage) {
  for (int scenery_num = 0; scenery_num < array_list_size(&game_stage->scenery_entities); scenery_num++) {
    struct Scenery* scenery = array_list_get(&game_stage->scenery_entities, scenery_num);
    scenery_delete(scenery, NULL);
    free(scenery);
  }

  array_list_delete(&game_stage->scenery_entities);
}
void game_stage_update(struct GameStage* game_stage, double delta_time) {}

//float draw_scale = 1.0f / 5.0f;
//
//// Load objects, reset unload/reload from scratch
//// Draw sprites from front to back for transparencies
//// Fore wood fence
//float fence_scale = draw_scale * 0.75f;
//for (int loop_num = 0; loop_num < 10; loop_num++) {
//  struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//  sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/forewoodfence.png"));
//  sprite->position = (vec3){.x = -3.0f - (loop_num * sprite->width) * 0.92f * fence_scale, .y = -3.125f, .z = -2.0f + loop_num * 0.000001f};
//  sprite->scale = (vec3){.x = fence_scale, .y = fence_scale, .z = fence_scale};
//  array_list_add(&game->sprites, sprite);
//}
//
//// HUD
////game->hud_sprite = calloc(1, sizeof(struct Sprite));
////sprite_init(game->hud_sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&game->texture_cache, "./assets/textures/hud.png"));
//////sprite->position = (vec3){.x = (loop_num * sprite->width) * 0.999f * draw_scale, .y = 10.0f, .z = 50.0f + (loop_num * 0.000001)};
////game->hud_sprite->position = (vec3){.x = game->camera.position.x, .y = game->camera.position.y, .z = -0.1f};
////game->hud_sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
////array_list_add(&game->sprites, game->hud_sprite);
//
//// Sandbox
//struct Sprite* sandbox_sprite = calloc(1, sizeof(struct Sprite));
//sprite_init(sandbox_sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/sandbox.png"));
//sandbox_sprite->position = (vec3){.x = -3.8f, .y = -1.5f, .z = 0.0f};
//sandbox_sprite->scale = (vec3){.x = draw_scale * 1.75, .y = draw_scale * 1.75, .z = draw_scale * 1.75};
//array_list_add(&game->sprites, sandbox_sprite);
//
//// Trash
//struct Sprite* trash_sprite = calloc(1, sizeof(struct Sprite));
//sprite_init(trash_sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/trash.png"));
//trash_sprite->position = (vec3){.x = -1.35f, .y = -0.125f, .z = 0.0f};
//trash_sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//array_list_add(&game->sprites, trash_sprite);
//struct Sprite* trash_sprite2 = calloc(1, sizeof(struct Sprite));
//sprite_init(trash_sprite2, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/trash2.png"));
//trash_sprite2->position = (vec3){.x = -3.8f, .y = -0.125f, .z = 0.0f};
//trash_sprite2->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//array_list_add(&game->sprites, trash_sprite2);
//
//// Sign
//struct Sprite* sign_sprite = calloc(1, sizeof(struct Sprite));
//sprite_init(sign_sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/sign.png"));
//sign_sprite->position = (vec3){.x = -2.3f, .y = 0.45f, .z = 0.0f};
//sign_sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//array_list_add(&game->sprites, sign_sprite);
//
//// Fence
//for (int loop_num = 0; loop_num < 10; loop_num++) {
//  struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//  sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/fence.png"));
//  sprite->position = (vec3){.x = 10.0f - (loop_num * sprite->width) * 0.92f * draw_scale, .y = 0.525f, .z = loop_num * 0.000001f};
//  sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//  array_list_add(&game->sprites, sprite);
//}
//
//// Grass
//for (int loop_num = 0; loop_num < 15; loop_num++) {
//  //if (loop_num <= 5) {
//  //  struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//  //  sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/street.png"));
//  //  sprite->position = (vec3){.x = 14.035f - (loop_num * sprite->width) * 0.995f * draw_scale, .y = -1.75, .z = 0.01 + (loop_num * 0.000001)};
//  //  sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//  //  array_list_add(&game->sprites, sprite);
//  //} else if (loop_num <= 7) {
//  if (loop_num <= 7) {
//    struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//    sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/grass.png"));
//    sprite->position = (vec3){.x = 14.0f - (loop_num * sprite->width) * 0.98f * draw_scale, .y = -1.675, .z = 0.01 + (loop_num * 0.000001)};
//    sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//    array_list_add(&game->sprites, sprite);
//  } else {
//    struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//    sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/grassshadow.png"));
//    sprite->position = (vec3){.x = 14.0f - (loop_num * sprite->width) * 0.98f * draw_scale, .y = -1.675, .z = 0.01 + (loop_num * 0.000001)};
//    sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//    array_list_add(&game->sprites, sprite);
//  }
//}
//
//// Wood fence
//for (int loop_num = 0; loop_num < 10; loop_num++) {
//  struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//  sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/woodfence.png"));
//  sprite->position = (vec3){.x = -4.37125f - (loop_num * sprite->width) * 0.92f * draw_scale, .y = 0.825f, .z = 0.011f + loop_num * 0.000001f};
//  sprite->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//  array_list_add(&game->sprites, sprite);
//}
//
//// Sign 2
//struct Sprite* sign_sprite2 = calloc(1, sizeof(struct Sprite));
//sprite_init(sign_sprite2, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/sign2.png"));
//sign_sprite2->position = (vec3){.x = 0.15f, .y = 1.1f, .z = 0.0111f};
//sign_sprite2->scale = (vec3){.x = draw_scale, .y = draw_scale, .z = draw_scale};
//array_list_add(&game->sprites, sign_sprite2);
//
//// Background
//struct Sprite* back_sprite = calloc(1, sizeof(struct Sprite));
//sprite_init(back_sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/back2.png"));
//back_sprite->position = (vec3){.x = 1.0f, .y = 1.1f, .z = 7.0f};
//back_sprite->scale = (vec3){.x = draw_scale * 2, .y = draw_scale * 2, .z = draw_scale * 2};
//array_list_add(&game->sprites, back_sprite);
//
//// Clouds
//float cloud_scale = 10.0f * draw_scale;
//for (int loop_num = 0; loop_num < 1; loop_num++) {
//  struct Sprite* sprite = calloc(1, sizeof(struct Sprite));
//  sprite_init(sprite, gpu_api, &game->sprite_shader.shader, texture_cache_get(&resource_manager->texture_cache, "./assets/textures/clouds.png"));
//  sprite->position = (vec3){.x = (loop_num * sprite->width) * 0.999f * draw_scale, .y = 10.0f, .z = 50.0f + (loop_num * 0.000001)};
//  sprite->scale = (vec3){.x = cloud_scale, .y = cloud_scale, .z = cloud_scale};
//  array_list_add(&game->sprites, sprite);
//}