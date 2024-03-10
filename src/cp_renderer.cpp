#include "cp_renderer.hpp"

bool GMCpRenderer::render(){
    VideoService* service = GMManager::get_instance()->get_video_service();
    GMSprite* sprite = get_current_sprite();
    for (int i = 0; i < sprite->h * sprite->w; ++i) {
        service->draw_image(*(sprite->tiles[i].image), sprite->tiles[i].boundaries, get_rect(i, sprite->h, sprite->w));
    }
}

GMSprite* GMCpRenderer::get_current_sprite() {
    return sprites;
}

GMRect GMCpRenderer::get_rect(uint16_t index, uint8_t w, uint8_t h) {
    return GMRect();
}
