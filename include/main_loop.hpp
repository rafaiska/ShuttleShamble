#ifndef _MAIN_LOOP_H_
#define _MAIN_LOOP_H_

#include <set>

#include "manager.hpp"
#include "camera.hpp"

class GMMainLoop {
    private:
        std::vector<GMObject*> stopped_objects;
        std::vector<GMObject*> moving_objects;
        std::vector<GMObject*> all_objects;
        std::vector<GMObject*> renderer_queue;
        GMCamera camera;

        void update_colliders();
        void update_renderers();
        void track_collision(GMObject* objectA, GMObject* objectB, std::set<GMObject*>& all_collided);

    public:
        void enqueue_collider(GMObject* collider);
        void enqueue_renderer(GMObject* object);
        void tick(float delta);
        void main_loop();
        GMObject* create_object();
        void clear_objects();
        void configure_camera(GMRect camera_transform) {camera.configure(camera_transform);}
        GMCamera& get_camera() {return camera;}
};

#endif