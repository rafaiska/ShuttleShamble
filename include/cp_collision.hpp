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
                GMCpCollider(GMRect transform, GMVector global_position);
                void update(float delta);
                void set_speed(GMVector new_speed);
                bool collided_with(const GMCpCollider& other);
                bool moved();
                void commit_position() {position = new_position;}
                void add_collided_with(GMCpCollider* other);
                std::vector<GMCpCollider*>& get_collided_with_others() {return collided_with_others;}
                GMVector get_position() const {return position;}
                GMVector get_new_position() const {return new_position;}
                GMRect get_transform() const {return transform;}
                void clear_collided_with() {collided_with_others.clear();}
};

#endif