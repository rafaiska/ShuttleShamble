#ifndef _MAIN_LOOP_H_
#define _MAIN_LOOP_H_

#include "manager.hpp"

class GMMainLoop {
        std::vector<GMCpCollider*> stopped_colliders;
        std::vector<GMCpCollider*> moving_colliders;
    public:
        void enqueue_collider(GMCpCollider* collider);
        void update_colliders();
        void tick(float delta);
        void main_loop();
};

#endif