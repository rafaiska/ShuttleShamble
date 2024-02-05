#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "video_service.hpp"

class GMManager {
    private:
        VideoService* service;
    
    public:
        void main_loop();
};

#endif