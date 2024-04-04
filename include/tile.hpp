#ifndef _TILE_H_
#define _TILE_H_

#include "image.hpp"
#include "utils.hpp"

class GMTile {
    GMImage2D image;
    GMRect boundaries;

    public:
        GMTile(GMImage2D image, GMRect boundaries);
        void set_image(std::string path, uint16_t w, uint16_t h);
        void set_boundaries(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
};

#endif