#ifndef _TILE_H_
#define _TILE_H_

#include "image.hpp"
#include "utils.hpp"

class GMTile {
    GMImage2D image;
    GMRect boundaries;
    uint8_t size;

    public:
        GMTile(GMImage2D image_, GMRect boundaries_);
        ~GMTile(){}
        void set_image(std::string path, uint16_t w, uint16_t h);
        void set_boundaries(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
        GMRect get_boundaries() const {return boundaries;}
        GMImage2D get_image() const {return image;}
        bool operator==(const GMTile& other) const;
        uint8_t get_size(){return size;}

        class TilesShouldBeSquare{};
};

#endif