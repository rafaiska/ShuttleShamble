#ifndef _GMTILEMAP_HPP_
#define _GMTILEMAP_HPP_

#include <vector>

#include "tile.hpp"
#include "data_tree.hpp"

class GMTileFrames
{
    std::vector<uint32_t> frames;
    uint8_t current_frame;
    uint8_t animation_mode;
};

class GMTileLayer
{
    std::vector<GMTileFrames> map;
    std::vector<uint32_t> animated_tiles_indexes;
};

class GMTileMap
{
    std::vector<GMTileLayer> layers;
    std::vector<GMTile> tileset;
    u_int32_t w;
    u_int32_t h;
    u_int8_t tile_size_h;
    u_int8_t tile_size_w;

    public:
        bool was_tileset_loaded() {return tileset.size() > 0;}
        void load_tileset_from_tiled_data_tree(GMDataTree& data_tree);
        void load_tilemap_from_tiled_data_tree(GMDataTree& data_tree);
};

#endif