#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <vector>

#include "video_service.hpp"
#include "game_object.hpp"

class GMManager {
    private:
        static VideoService* service;
        static std::vector<GMObject> objects;
    
    public:
        static void start_test_services();
        static std::vector<GMObject> get_objects() {return objects;}
};

#endif