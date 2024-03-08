#include "video_service_sdl1.hpp"
#include <iostream>

void VideoServiceSDL1::init() {
    status = SDL_Init(SDL_INIT_VIDEO);
    main_surface = SDL_SetVideoMode(160, 144, 0, SDL_ANYFORMAT);
}

void VideoServiceSDL1::exit() {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool VideoServiceSDL1::draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect) {
    SDL_Surface* img_surface = IMG_Load(image.image_path.c_str());
    if (img_surface == NULL) {
        std::cout << "COULDN'T LOAD IMAGE FILE: " + image.image_path;
    }
    SDL_Rect src_rect_sdl, dst_rect_sdl;
    sdlrect_from_gmrect(src_rect, src_rect_sdl);
    sdlrect_from_gmrect(dst_rect, dst_rect_sdl);
    SDL_BlitSurface(img_surface, &src_rect_sdl, main_surface, &dst_rect_sdl);
    return false;
}

bool VideoServiceSDL1::clear_canvas() {
    SDL_UpdateRect(main_surface, 0, 0, 0, 0);
    SDL_FillRect(main_surface, NULL, 0);
    return false;
}

void VideoServiceSDL1::sdlrect_from_gmrect(GMRect& src, SDL_Rect& dst) {
    dst.h = src.h;
    dst.w = src.w;
    dst.x = src.x;
    dst.y = src.y;
}