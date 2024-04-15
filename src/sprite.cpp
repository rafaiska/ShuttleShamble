#include "sprite.hpp"

GMSprite::~GMSprite()
{
    this->tiles.clear();
}

void GMSprite::add_tile(GMTile tile)
{
    if (this->tiles.size() >= (this->columns * this->rows))
        throw MaxTilesExceeded();
    
    if (tile.get_size() != this->tile_size)
        throw WrongTileSize();
    
    this->tiles.push_back(tile);
}

GMTile GMSprite::get_tile(uint8_t column, uint8_t row)
{
    if (column >= columns || row >= rows)
        throw TileIndexError();
    
    return tiles[column + row*columns];
}
