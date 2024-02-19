#ifndef __GRAPHICS2D_H__
#define __GRAPHICS2D_H__

#include<cstdint>
#include<string>

struct GMImage2D {
    std::string image_path;
    uint8_t w;
    uint8_t h;

    public:
        GMImage2D(std::string path) {this->image_path = path;}
};

#endif