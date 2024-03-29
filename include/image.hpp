#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <cstdint>

class GMImage2D {
    std::string image_path;
    uint16_t w;
    uint16_t h;

    public:
        GMImage2D() {GMImage2D("", 0, 0);}
        GMImage2D(std::string path, uint16_t w, uint16_t h) {this->image_path = path; this->w = w; this->h = h;}
        void set_path(std::string path) {this->image_path = path;}
        void set_dimensions(uint16_t w, uint16_t h) {this->w = w; this->h = h;}
};

#endif