#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <vector>
#include <unordered_map>
#include <string>

#include "video_service.hpp"
#include "game_object.hpp"
#include "cp_handler.hpp"

class GMManager {
    protected:
        static GMManager* manager;
        VideoService* video_service;
        std::vector<GMObject*> objects;
        std::unordered_map<std::string, GMCpHandler*> handlers;

        GMManager(){}
    
    public:
        static GMManager* get_instance();
        void start_test_services();
        std::vector<GMObject*> get_objects() {return objects;}
        void log_error(GMObject* object, std::string message);
        GMCpHandler* get_handler(std::string handler_name) {return handlers.at(handler_name);}
};

#endif