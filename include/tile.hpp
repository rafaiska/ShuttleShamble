#ifndef _TILE_H_
#define _TILE_H_

#include "image.hpp"
#include "utils.hpp"

class GMTile {
    GMImage2D image;
    GMRect boundaries;

    public:
        GMTile();
};

#endif