#include "sprite.hpp"

GMSprite::~GMSprite()
{
    for(GMTile* tile: this->tiles) {
        delete tile;
    }
    this->tiles.clear();
}

uint8_t GMSprite::add_tile(GMTile* tile)
{
    if (this->tiles.size() >= (this->h * this->w))
        throw MaxTilesExceeded();
    
    this->tiles.push_back(tile);
    return 0;
}

GMTile *GMSprite::get_tile(uint8_t x, uint8_t y)
{
    if (x >= w || y >= h)
        throw TileIndexError();
    
    return tiles[x + y*w];
}
