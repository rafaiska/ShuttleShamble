#include "cp_renderer.hpp"

GMCpRenderer::~GMCpRenderer()
{
    sprites.clear();
}

void GMCpRenderer::add_sprite(GMSprite sprite)
{
    GMSprite _sprite = sprite;
    sprites.push_back(_sprite);
}

void GMCpRenderer::update(float delta)
{
}

GMSprite GMCpRenderer::get_current_sprite() {
    return sprites[0]; //TODO: This is part of animation logic, TBD
}

GMRect GMCpRenderer::get_rect(uint16_t index, uint8_t w, uint8_t h) {
    return GMRect();
}
