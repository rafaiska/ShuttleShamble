#ifndef __VIDEO_SERVICE_H_
#define __VIDEO_SERVICE_H_

#include <cstdint>
#include "graphics2d.hpp"

class VideoService {
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect) = 0;
    virtual bool clear_canvas() = 0;
};

class VideoServiceSDL1: public VideoService {

};

#endif