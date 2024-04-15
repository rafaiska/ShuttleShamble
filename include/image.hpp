#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <cstdint>

class GMImage2D {
    std::string image_path;
    uint16_t w;
    uint16_t h;

    public:
        GMImage2D(std::string path_="", uint16_t w_=0, uint16_t h_=0): image_path(path_), w(w_), h(h_) {}
        void set_path(std::string path) {this->image_path = path;}
        void set_dimensions(uint16_t w, uint16_t h) {this->w = w; this->h = h;}
        bool operator==(const GMImage2D &other) const;
        GMImage2D& operator=(GMImage2D& other);
};

#endif