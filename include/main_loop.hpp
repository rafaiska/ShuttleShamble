#ifndef _MAIN_LOOP_H_
#define _MAIN_LOOP_H_

#include "manager.hpp"

class GMMainLoop {
    public:
        void tick(float delta);
        void main_loop();
};

#endif