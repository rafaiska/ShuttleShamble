#ifndef _CP_RENDERER_H_
#define _CP_RENDERER_H_

#include "sprite.hpp"

#define ANIMATION_MODE_STATIC 0

class GMCpRenderer {
    private:
        std::vector<GMSprite> sprites;
        uint8_t animation_mode;
        bool _is_visible;
        GMRect transform;

        GMSprite get_current_sprite();
        GMRect get_rect(uint16_t index, uint8_t w, uint8_t h);
    public:
        GMCpRenderer(){}
        ~GMCpRenderer();
        bool is_visible() const {return _is_visible;}
        void add_sprite(GMSprite sprite);
        GMSprite get_sprite(int index) {return sprites[index];}
        void update(float delta);
        GMRect& get_transform() {return transform;}
};

#endif