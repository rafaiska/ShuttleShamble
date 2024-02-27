#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include <string>

#include "utils.hpp"

class GMCpCollider {
        private:
                GMVector position;
                GMVector new_position;
                GMVector speed;
                uint8_t collision_mask;
                uint8_t elasticity;
                std::string collider_tag;
        public:
                GMCpCollider(GMVector position) {this->position = GMVector(position.x, position.y);}
                void update(float delta);
                void set_speed(GMVector new_speed);
                bool collided_with(const GMCpCollider& other);
                bool moved() {return new_position.x != position.x || new_position.y != position.y;}
                void reset_position() {new_position.x = position.x; new_position.y = position.y;}
                void commit_position() {position.x = new_position.x; position.y = new_position.y;}
};

#endif