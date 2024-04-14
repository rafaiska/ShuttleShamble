#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#define SPRITE_NUMBER_OF_TILES_EXCEEDED 1

#include<vector>

#include "tile.hpp"

class GMSprite {
    private:
        std::vector<GMTile> tiles;
        uint8_t tile_size;
        uint8_t columns;
        uint8_t rows;
    public:
        GMSprite(uint8_t columns_, uint8_t rows_, uint8_t tile_size_): columns(columns_), rows(rows_), tile_size(tile_size_){}
        ~GMSprite();
        void add_tile(GMTile tile);
        GMTile get_tile(uint8_t x, uint8_t y);
        std::vector<GMTile> get_tiles() {return tiles;}
        uint8_t get_tile_size() {return tile_size;}
        uint8_t get_columns() {return columns;}
        uint8_t get_rows() {return rows;}

        class MaxTilesExceeded{};
        class TileIndexError{};
        class WrongTileSize{};
};

#endif