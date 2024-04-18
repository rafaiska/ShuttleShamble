#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include <string>
#include <vector>

#include "utils.hpp"

class GMCpCollider {
        private:
                GMVector position;
                GMVector new_position;
                GMVector speed;
                uint8_t collision_mask;
                uint8_t elasticity;
                std::string collider_tag;
                std::vector<GMCpCollider*> collided_with_others;
                GMRect transform;
        public:
                GMCpCollider(GMRect transform);
                void update(float delta);
                void set_speed(GMVector new_speed);
                bool collided_with(const GMCpCollider& other);
                bool moved();
                void reset_position() {new_position.x = position.x; new_position.y = position.y;}
                void commit_position() {position.x = new_position.x; position.y = new_position.y;}
                void add_collided_with(GMCpCollider* other);
                std::vector<GMCpCollider*> get_collided_with_others() const {return collided_with_others;}
                GMVector get_position() const {return position;}
};

#endif