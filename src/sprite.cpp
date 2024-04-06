#include "sprite.hpp"

GMSprite::~GMSprite()
{
    this->tiles.clear();
}

void GMSprite::add_tile(GMTile tile)
{
    if (this->tiles.size() >= (this->h * this->w))
        throw MaxTilesExceeded();
    
    GMTile new_tile = tile;
    this->tiles.push_back(new_tile);
}

GMTile GMSprite::get_tile(uint8_t x, uint8_t y)
{
    if (x >= w || y >= h)
        throw TileIndexError();
    
    return tiles[x + y*w];
}
