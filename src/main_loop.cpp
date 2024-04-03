#include "main_loop.hpp"

GMObject* GMMainLoop::create_object() {
    GMObject* new_obj = new GMObject();
    objects.push_back(new_obj);
    return new_obj;
}

void GMMainLoop::clear_objects() {
    for (GMObject* obj: objects) {
        delete obj;
    }
    objects.clear();
}

void GMMainLoop::enqueue_collider(GMCpCollider* collider)
{
    if (collider != nullptr) {
        if (collider->moved())
            moving_colliders.push_back(collider);
        else
            stopped_colliders.push_back(collider);
    }
}

void GMMainLoop::enqueue_renderer(GMCpRenderer *renderer)
{
    if (renderer != nullptr && renderer->is_visible()) {
        renderers.push_back(renderer);
    }
}

void GMMainLoop::update_colliders()
{
    std::set<GMCpCollider*> collided;

    for (int i=0; i < moving_colliders.size(); i++) {
        if (!moving_colliders[i]->moved())
            continue;
        
        for (int j=i+1; j < moving_colliders.size(); j++) {
            if (moving_colliders[i]->collided_with(*moving_colliders[j])) 
            {
                track_colliders(moving_colliders[i], moving_colliders[j], collided);
            }
        }

        for (GMCpCollider* stopped_collider: stopped_colliders) {
            if (moving_colliders[i]->collided_with(*stopped_collider)) 
            {
                track_colliders(moving_colliders[i], stopped_collider, collided);
            }
        }
    }

    moving_colliders.clear();
    stopped_colliders.clear();
}

void GMMainLoop::update_renderers()
{
}

void GMMainLoop::track_colliders(GMCpCollider* colliderA, GMCpCollider* colliderB, std::set<GMCpCollider*>& collider_set) {
    colliderA->set_collided_with(colliderB);
    collider_set.insert(colliderA);

    colliderB->set_collided_with(colliderA);
    collider_set.insert(colliderB);
}

void GMMainLoop::tick(float delta)
{
    for (GMObject *object : objects) {
        object->update(delta);
        enqueue_collider(object->get_collider());
        enqueue_renderer(object->get_renderer());
    }
    update_colliders();
    update_renderers();
}

void GMMainLoop::main_loop()
{
    while (true)
    {
        tick(1.0);
    }
}