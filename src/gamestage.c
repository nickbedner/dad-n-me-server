#include "gamestage.h"

int game_stage_init(struct GameState* game_stage) {
  // Load stage from file
  texture_cache_init(&resource_manager->texture_cache);
  struct XmlNode* texture_list_node = xml_parser_load_xml_file("./assets/stages/gamestage.xml");
  const char* texture_list_key = NULL;
  struct MapIter texture_list_iter = map_iter();

  struct TextureSettingsBucket {
    struct TextureSettings texture_settings[64];
    char file_path[64][2048];
    struct XmlNode* node[64];
  } texture_settings_bucket = {0};

  int total_texture_num = 0;
  while ((texture_list_key = map_next(texture_list_node->child_nodes, &texture_list_iter)))
    texture_settings_bucket.node[total_texture_num++] = array_list_get(*((struct ArrayList**)map_get(texture_list_node->child_nodes, texture_list_key)), 0);
#pragma omp parallel for schedule(dynamic)
  for (int texture_num = 0; texture_num < total_texture_num; texture_num++) {
    strcpy(texture_settings_bucket.file_path[texture_num], "./assets/textures/");
    char* current_node_path = xml_node_get_data(xml_node_get_child(texture_settings_bucket.node[texture_num], "path"));
    strcat(texture_settings_bucket.file_path[texture_num], current_node_path);
    texture_settings_bucket.texture_settings[texture_num] = (struct TextureSettings){.path = texture_settings_bucket.file_path[texture_num], .filter_type = FILTER_LINEAR, .mode_type = MODE_CLAMP_TO_BORDER, .mip_maps_enabled = 1, .premultiplied_alpha = 0};
  }
  texture_cache_add_bulk(&resource_manager->texture_cache, gpu_api, total_texture_num, texture_settings_bucket.texture_settings);
  xml_parser_delete(texture_list_node);

  return 0;
}
void game_stage_delete(struct GameState* game_stage) {}
void game_stage_update(struct GameState* game_stage, double delta_time) {}