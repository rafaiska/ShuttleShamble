#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include "game_component.hpp"
#include "utils.hpp"

class GMCpCollider: public GMComponent {
        private:
                GMVector position;
                GMVector new_position;
                GMVector speed;
                uint8_t collision_mask;
                uint8_t elasticity;
                std::string collider_type;
        public:
                GMCpCollider(GMVector position) {this->position = GMVector(position.x, position.y);}
                std::string get_name(){return "GMCpCollider";}
                void update(float delta);
                void set_speed(GMVector new_speed);
                bool collided_with(GMCpCollider other);
};

#endif