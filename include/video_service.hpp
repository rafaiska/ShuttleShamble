#ifndef __VIDEO_SERVICE_H_
#define __VIDEO_SERVICE_H_

#include <cstdint>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphics2d.hpp"
#include "utils.hpp"

class VideoService {
    public:
    virtual void init() = 0;
    virtual void exit() = 0;
    virtual bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect) = 0;
    virtual bool clear_canvas() = 0;
    virtual uint8_t get_status() = 0;
};

class VideoServiceMock: public VideoService {
    public:
        void init(){}
        virtual void exit(){}
        virtual bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect){return true;}
        virtual bool clear_canvas(){return true;}
        virtual uint8_t get_status(){return 0;}
};

class VideoServiceSDL1: public VideoService {
    uint8_t status;
    SDL_Surface* main_surface;

    public:
    void init();
    void exit();
    bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect);
    bool clear_canvas();
    uint8_t get_status(){return this->status;}

    private:
    void sdlrect_from_gmrect(GMRect& src, SDL_Rect& dst);
};

#endif