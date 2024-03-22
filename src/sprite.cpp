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
    if (this->tiles.size() >= (this->h * this->w) - 1)
        return SPRITE_NUMBER_OF_TILES_EXCEEDED;
    
    this->tiles.push_back(tile);
    return 0;
}