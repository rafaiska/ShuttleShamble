#ifndef _CP_RENDERER_H_
#define _CP_RENDERER_H_

#include "graphics2d.hpp"

class GMCpRenderer {
    private:
        GMSprite* sprites;
        uint8_t n_sprites;
        uint8_t animation_mode;
};

#endif