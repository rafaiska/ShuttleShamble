#include "video_service.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    VideoService* service = new VideoServiceSDL1();
    service->init();
    std::cout << "Video service status: " + std::to_string(service->get_status()) + "\n";
    service->draw_image(GMImage2D("assets/GBStyledSPrites.png"), GMRect(160, 144, 0, 0), GMRect(160, 144, 0, 0));
    service->clear_canvas();
    SDL_Delay(1000);
    service->exit();
    return 0;
}