#include "manager.hpp"

#include <iostream>

GMManager* GMManager::manager = nullptr;

GMManager::GMManager()
{
}

GMManager* GMManager::get_instance() {
    if(manager == nullptr) {
        manager = new GMManager();
    }
    return manager;
}

void GMManager::start_test_services() {
    video_service = new VideoServiceMock();
}

void GMManager::log_error(GMObject* object, std::string message)
{
    std::cout << message;
}
