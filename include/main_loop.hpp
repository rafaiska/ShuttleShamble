#ifndef _MAIN_LOOP_H_
#define _MAIN_LOOP_H_

#include <set>

#include "manager.hpp"

class GMMainLoop {
    private:
        std::vector<GMCpCollider*> stopped_colliders;
        std::vector<GMCpCollider*> moving_colliders;
        std::vector<GMObject*> objects;

        void update_colliders();
        void track_colliders(GMCpCollider* colliderA, GMCpCollider* colliderB, std::set<GMCpCollider*>& collider_set);

    public:
        void enqueue_collider(GMCpCollider* collider);
        void tick(float delta);
        void main_loop();
        GMObject* create_object();
        void clear_objects();
};

#endif