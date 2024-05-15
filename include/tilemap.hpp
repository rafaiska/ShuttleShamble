#ifndef _GMTILEMAP_HPP_
#define _GMTILEMAP_HPP_

#include <vector>

#include "tile.hpp"

class GMTileFrames
{
    std::vector<GMTile> frames;
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
    u_int32_t w;
    u_int32_t h;
    u_int8_t tile_size_h;
    u_int8_t tile_size_w;
};

#endif