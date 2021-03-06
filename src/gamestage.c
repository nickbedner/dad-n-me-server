/*#include "gamestage.h"

// Design stages as chunks going from left to right
// Then attach each stage chunk to allow easy moving of assets

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
    float scale = atof(xml_node_get_data(xml_node_get_child(texture_settings_bucket.node[scenery_num], "scale")));
    int repeat_factor = atoi(xml_node_get_data(xml_node_get_child(texture_settings_bucket.node[scenery_num], "repeat")));
    float offset = atof(xml_node_get_data(xml_node_get_child(texture_settings_bucket.node[scenery_num], "offset")));
    scenery_init(texture_settings_bucket.scenery[scenery_num], xml_node_get_attribute(position_node, "path"), scale, repeat_factor, offset);
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

void game_stage_update(struct GameStage* game_stage, double delta_time) {
}
*/