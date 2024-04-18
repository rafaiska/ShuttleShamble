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

        GMSprite get_sprite(int index) {return sprites[index];}
    public:
        GMCpRenderer(){}
        GMCpRenderer(GMRect transform_): transform(transform_){};
        ~GMCpRenderer();
        bool is_visible() const {return _is_visible;}
        void add_sprite(GMSprite sprite);
        GMSprite get_current_sprite();
        void update(float delta);
        GMRect& get_transform() {return transform;}
        void toggle_visible(bool toggle) { _is_visible = toggle;}
};

#endif