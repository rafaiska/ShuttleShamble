#ifndef __VIDEO_SERVICE_H_
#define __VIDEO_SERVICE_H_

#include <cstdint>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "tile.hpp"
#include "utils.hpp"

class VideoService {
    public:
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual bool draw_tile(const GMTile& tile, const GMVector& position) = 0;
    virtual bool clear_canvas() = 0;
    virtual uint8_t get_status() = 0;
};

#endif