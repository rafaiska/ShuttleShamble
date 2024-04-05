#include "cp_renderer.hpp"

GMCpRenderer::~GMCpRenderer()
{
    for (GMSprite* s : sprites)
    {
        delete s;
    }
    sprites.clear();
}

GMSprite* GMCpRenderer::get_current_sprite() {
    return sprites[0]; //TODO: This is part of animation logic, TBD
}

GMRect GMCpRenderer::get_rect(uint16_t index, uint8_t w, uint8_t h) {
    return GMRect();
}
