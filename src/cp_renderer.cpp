#include "cp_renderer.hpp"

GMCpRenderer::~GMCpRenderer()
{
    for (int i = 0; i < n_sprites; ++i)
    {
        delete(sprites + i);
    }
}

bool GMCpRenderer::render(){
    GMSprite* sprite = get_current_sprite();
    draw_tiles(sprite);
}

bool GMCpRenderer::draw_tiles(GMSprite* sprite) {
    VideoService* service = GMManager::get_instance()->get_video_service();
    for (int i = 0; i < sprite->h * sprite->w; ++i) {
        service->draw_tile(sprite->tiles[i], position + get_tile_relative_position(sprite, i));
    }
}

GMSprite* GMCpRenderer::get_current_sprite() {
    return sprites;
}

GMRect GMCpRenderer::get_rect(uint16_t index, uint8_t w, uint8_t h) {
    return GMRect();
}
