#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#include<cstdint>
#include<string>

#define ANIMATION_MODE_STATIC 0

struct GMImage2D {
    std::string image_path;
    uint8_t w;
    uint8_t h;

    public:
        GMImage2D(std::string path) {this->image_path = path;}
};

struct GMTile {
    GMImage2D* image;
    GMRect boundaries;
};

struct GMSprite {
    GMTile* tiles;
    uint8_t w;
    uint8_t h;
};

#endif