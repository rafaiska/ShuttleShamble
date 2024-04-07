#ifndef _MAIN_LOOP_H_
#define _MAIN_LOOP_H_

#include <set>

#include "manager.hpp"
#include "camera.hpp"

class GMMainLoop {
    private:
        std::vector<GMCpCollider*> stopped_colliders;
        std::vector<GMCpCollider*> moving_colliders;
        std::vector<GMObject*> objects;
        std::vector<GMCpRenderer*> renderers;
        GMCamera camera;

        void update_colliders();
        void update_renderers();
        void track_colliders(GMCpCollider* colliderA, GMCpCollider* colliderB, std::set<GMCpCollider*>& collider_set);

    public:
        void enqueue_collider(GMCpCollider* collider);
        void enqueue_renderer(GMCpRenderer* renderer);
        void tick(float delta);
        void main_loop();
        GMObject* create_object();
        void clear_objects();
        void configure_camera(GMRect camera_transform) {camera.configure(camera_transform);}
        GMCamera& get_camera() {return camera;}
};

#endif