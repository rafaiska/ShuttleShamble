#include "main_loop.hpp"

void GMMainLoop::enqueue_collider(GMCpCollider* collider)
{
    if (collider != nullptr) {
        if (collider->moved())
            moving_colliders.push_back(collider);
        else
            stopped_colliders.push_back(collider);
    }
}

void GMMainLoop::update_colliders()
{
    for (int i=0; i < moving_colliders.size(); i++) {
        if (!moving_colliders[i]->moved())
            continue;
        
        for (int j=i+1; j < moving_colliders.size(); j++) {
            if (moving_colliders[i]->collided_with(*moving_colliders[j])) 
            {
                moving_colliders[i]->reset_position();
                continue;
            }
        }

        for (GMCpCollider* stopped_collider: stopped_colliders) {

        }
    }
}

void GMMainLoop::tick(float delta)
{
    for (GMObject *object : GMManager::get_instance()->get_objects()) {
        object->update(delta);
        enqueue_collider(object->get_collider());
    }
    update_colliders();
}

void GMMainLoop::main_loop()
{
    while (true)
    {
        tick(1.0);
    }
}