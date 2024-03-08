#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <vector>
#include <unordered_map>
#include <string>

#include "video_service_mock.hpp"
#include "game_object.hpp"

class GMManager {
    protected:
        static GMManager* manager;
        VideoService* video_service;

        GMManager();
    
    public:
        static GMManager* get_instance();
        void start_test_services();
        void log_error(GMObject* object, std::string message);
        VideoService* get_video_service(){return video_service;}
};

#endif