#include "cp_renderer.hpp"

GMCpRenderer::~GMCpRenderer()
{
    for (int i = 0; i < n_sprites; ++i)
    {
        delete(sprites + i);
    }
}

GMSprite* GMCpRenderer::get_current_sprite() {
    return sprites;
}

GMRect GMCpRenderer::get_rect(uint16_t index, uint8_t w, uint8_t h) {
    return GMRect();
}
