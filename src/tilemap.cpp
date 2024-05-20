#include "tilemap.hpp"

void GMTileMap::load_tileset_from_tiled_data_tree(GMDataTree &data_tree)
{
    GMDataNode* tileset_node = data_tree.FirstChildElement("tileset");
    uint32_t tile_width = tileset_node->IntAttribute("tilewidth");
    uint32_t tile_height = tileset_node->IntAttribute("tilewidth");
    GMDataNode* image_node = tileset_node->FirstChildElement("image");
    uint32_t image_width = image_node->IntAttribute("width");
    uint32_t image_height = image_node->IntAttribute("height");
    
}

void GMTileMap::load_tilemap_from_tiled_data_tree(GMDataTree &data_tree)
{
}
