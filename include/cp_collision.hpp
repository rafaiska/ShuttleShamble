#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include "game_component.hpp"
#include "utils.hpp"

class GMCpCollision: public GMComponent {
        private:
                GMVector position;
                GMVector new_position;
                GMVector speed;
                uint8_t collision_mask;
                uint8_t elasticity;
                std::string collider_type;
        public:
                GMCpCollision(GMVector position) {this->position = position;}
                std::string get_name(){return "GMCpCollision";}
                void update(float delta);
                void set_speed(GMVector new_speed);
};

#endif