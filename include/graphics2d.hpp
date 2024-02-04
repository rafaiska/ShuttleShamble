#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#include<cstdint>
#include<string>

struct GMRect {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;
    GMRect(uint32_t w, uint32_t h, uint32_t x, uint32_t y) {this->w = w;this->h = h;this->x = x;this->y = y;}
};

struct GMImage2D {
    std::string image_path;

    public:
        GMImage2D(std::string path) {this->image_path = path;}
};

#endif