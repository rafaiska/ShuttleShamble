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

void GMMainLoop::enqueue_renderer(GMObject* object)
{
    if (object->get_renderer() != nullptr && object->get_renderer()->is_visible()) {
        renderer_queue.push_back(object);
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
    GMVector camera_position = get_position_from_rect(camera.get_transform());
    while (renderer_queue.size() > 0)
    {
        GMObject* rendered_object = renderer_queue.back();
        renderer_queue.pop_back();
        
        uint8_t tile_size = rendered_object->get_renderer()->get_current_sprite().get_tile_size();
        GMVector renderer_global_pos = get_position_from_rect(rendered_object->get_renderer_global_rect());
        GMSprite sprite = rendered_object->get_renderer()->get_current_sprite();

        for (uint8_t r=0; r < sprite.get_rows(); ++r)
            for (uint8_t c=0; c < sprite.get_columns(); ++c)
            {
                GMTile tile = sprite.get_tile(c, r);
                if(camera.is_tile_visible(tile, renderer_global_pos))
                {
                    GMVector tile_position = renderer_global_pos;
                    tile_position = tile_position + GMVector(c * tile_size, r * tile_size);
                    GMManager::get_instance()->get_video_service()->draw_tile(tile, tile_position, camera_position);
                }
            }
    }
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
        enqueue_renderer(object);
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