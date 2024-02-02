#include "video_service.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    VideoService* service = new VideoServiceSDL1();
    service->init();
    std::cout << "Video service status: " + std::to_string(service->get_status()) + "\n";
    service->exit();
    return 0;
}