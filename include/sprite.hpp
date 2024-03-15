#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#include<vector>

#include "tile.hpp"

#define ANIMATION_MODE_STATIC 0

class GMSprite {
    private:
        std::vector<GMTile> tiles;
        uint8_t w;
        uint8_t h;
    public:
        ~GMSprite();
};

#endif