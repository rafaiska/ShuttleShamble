#include "tilemap.hpp"

void GMTileMap::load_tileset_from_tiled_data_tree(GMDataTree &data_tree)
{
    GMDataNode* tileset_node = data_tree.FirstChildElement("tileset");
}

void GMTileMap::load_tilemap_from_tiled_data_tree(GMDataTree &data_tree)
{
}
