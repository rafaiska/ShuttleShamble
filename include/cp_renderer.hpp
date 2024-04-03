#ifndef _CP_RENDERER_H_
#define _CP_RENDERER_H_

#include "sprite.hpp"

class GMCpRenderer {
    private:
        GMSprite* sprites;
        uint8_t n_sprites;
        uint8_t animation_mode;
        bool _is_visible;

        GMSprite* get_current_sprite();
        GMRect get_rect(uint16_t index, uint8_t w, uint8_t h);
    public:
        GMCpRenderer(){}
        ~GMCpRenderer();
        bool is_visible(){return _is_visible;}
};

#endif