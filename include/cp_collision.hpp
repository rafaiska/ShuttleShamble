#ifndef _CP_COLLISION_H_
#define _CP_COLLISION_H_

#include <string>

#include "utils.hpp"

class GMCpCollider {
        private:
                GMVector position;
                GMVector new_position;
                GMVector speed;
                float aura_radius;
                uint8_t collision_mask;
                uint8_t elasticity;
                std::string collider_tag;
                GMCpCollider* collided_with_other;
        public:
                GMCpCollider(const GMVector& position, float aura_radius);
                void update(float delta);
                void set_speed(GMVector new_speed);
                bool collided_with(const GMCpCollider& other);
                bool moved();
                void reset_position() {new_position.x = position.x; new_position.y = position.y;}
                void commit_position() {position.x = new_position.x; position.y = new_position.y;}
                void set_collided_with(GMCpCollider* other);
                GMCpCollider* get_collided_with(){return collided_with_other;}
                void set_aura_radius(float new_radius){aura_radius = new_radius;}
                float get_aura_radius() const {return aura_radius;}
                GMVector get_position() const {return position;}
};

#endif