#ifndef _VIDEO_SERVICE_SDL1_H_
#define _VIDEO_SERVICE_SDL1_H_

#include "video_service.hpp"

class VideoServiceSDL1: public VideoService {
    uint8_t status;
    SDL_Surface* main_surface;

    public:
    void init();
    void exit();
    bool draw_tile(const GMTile& tile, const GMVector& tile_position, const GMVector& camera_position);
    bool clear_canvas();
    uint8_t get_status(){return this->status;}

    private:
    void sdlrect_from_gmrect(GMRect& src, SDL_Rect& dst);
};

#endif