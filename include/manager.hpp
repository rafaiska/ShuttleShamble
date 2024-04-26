#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <vector>
#include <unordered_map>
#include <string>

#include "video_service_mock.hpp"
#include "file_service.hpp"
#include "game_object.hpp"
#include "asset_manager.hpp"

class GMManager {
    protected:
        static GMManager* manager;
        VideoService* video_service = nullptr;
        FileService* file_service = nullptr;
        AssetManager* asset_manager = nullptr;

        GMManager();
    
    public:
        static GMManager* get_instance();
        void start_test_services();
        void log_error(GMObject* object, std::string message);
        VideoService* get_video_service(){return video_service;}
        FileService* get_file_service(){return file_service;}
        FileService* start_file_service();
        AssetManager* start_asset_manager();
        AssetManager* get_asset_manager() {return asset_manager;}
        void shutdown_asset_manager();

        class FileServiceMustBeInitialized{};
};

#endif