#include "video_service_sdl1.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    VideoService* service = new VideoServiceSDL1();
    service->init();
    std::cout << "Video service status: " + std::to_string(service->get_status()) + "\n";
    std::cout << "SDL_GetError: " + std::string(SDL_GetError()) + "\n";
    service->draw_tile(GMTile(GMImage2D("src/test/assets/sample.png", 16, 16), GMRect(16, 16, 0, 0)), GMVector(10, 10), GMVector(0, 0));
    service->clear_canvas();
    SDL_Delay(1000);
    service->exit();
    return 0;
}