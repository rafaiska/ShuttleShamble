#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <cstdint>

class GMImage2D {
    std::string image_path;
    uint8_t w;
    uint8_t h;

    public:
        GMImage2D() {GMImage2D("");}
        GMImage2D(std::string path) {this->image_path = path;}
        GMImage2D operator=(const GMImage2D& rhs) {this->image_path = rhs.image_path; this->w = rhs.w; this->h = rhs.h; return *this;}
};

#endif