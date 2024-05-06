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
    if (video_service == nullptr)
        video_service = new VideoServiceMock();
    start_file_service();
}

void GMManager::log_error(GMObject* object, std::string message)
{
    std::cout << message;
}

FileService *GMManager::start_file_service()
{
    if (file_service == nullptr)
        file_service = new FileService();
    return file_service;
}

AssetManager *GMManager::start_asset_manager()
{
    if (file_service == nullptr)
        throw FileServiceMustBeInitialized();
    asset_manager = new AssetManager(file_service);
    return asset_manager;
}

void GMManager::shutdown_asset_manager()
{
    if (asset_manager != nullptr)
    {
        delete asset_manager;
        asset_manager = nullptr;
    }
}
