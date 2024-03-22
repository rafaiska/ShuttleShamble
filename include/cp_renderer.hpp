#ifndef _CP_RENDERER_H_
#define _CP_RENDERER_H_

#include "sprite.hpp"
#include "manager.hpp"

class GMCpRenderer {
    private:
        GMSprite* sprites;
        uint8_t n_sprites;
        uint8_t animation_mode;

        GMSprite* get_current_sprite();
        bool draw_tiles(GMSprite* sprite);
        GMRect get_rect(uint16_t index, uint8_t w, uint8_t h);
    public:
        GMCpRenderer(){}
        ~GMCpRenderer();
        bool render();
};

#endif