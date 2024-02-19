#include "manager.hpp"

GMManager* GMManager::get_instance() {
    if(manager == nullptr) {
        manager = new GMManager();
    }
    return manager;
}

void GMManager::start_test_services() {
    video_service = new VideoServiceMock();
}