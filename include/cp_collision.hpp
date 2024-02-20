#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include "game_component.hpp"

class GMCpCollision: public GMComponent {
        public:
        std::string get_name(){return "GMCpCollision";}
        void update(float delta);
};

#endif