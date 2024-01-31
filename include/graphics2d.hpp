#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#include<cstdint>
#include<string>

struct GMRect {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;
};

struct GMImage2D {
    std::string image_path;
};

#endif