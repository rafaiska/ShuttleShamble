#include "video_service.hpp"

void VideoServiceSDL1::init() {
    status = SDL_Init(SDL_INIT_VIDEO);
}

void VideoServiceSDL1::exit() {
    SDL_Quit();
}

bool VideoServiceSDL1::draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect) {
    return false;
}

bool VideoServiceSDL1::clear_canvas() {
    return false;
}