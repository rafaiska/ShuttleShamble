#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <vector>

#include "video_service.hpp"
#include "game_object.hpp"

class GMManager {
    protected:
        static GMManager* manager;
        static VideoService* video_service;
        static std::vector<GMObject> objects;

        GMManager(){}
    
    public:
        static GMManager* get_instance();
        void start_test_services();
        std::vector<GMObject> get_objects() {return objects;}
        void log_error(GMObject* object, std::string message);
};

#endif