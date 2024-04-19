#include "main_loop.hpp"

GMObject* GMMainLoop::create_object() {
    GMObject* new_obj = new GMObject();
    all_objects.push_back(new_obj);
    return new_obj;
}

void GMMainLoop::clear_objects() {
    for (GMObject* obj: all_objects) {
        delete obj;
    }
    all_objects.clear();
}

void GMMainLoop::enqueue_collider(GMObject* object)
{
    GMCpCollider* collider = object->get_collider();
    if (collider != nullptr) {
        collider->clear_collided_with();
        if (collider->moved())
            moving_objects.push_back(object);
        else
            stopped_objects.push_back(object);
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
    std::set<GMObject*> collided;

    for (int i=0; i < moving_objects.size(); i++) {      
        for (int j=i+1; j < moving_objects.size(); j++) {
            track_collision(moving_objects[i], moving_objects[j], collided);
        }

        for (GMObject* stopped_object: stopped_objects) {
            track_collision(moving_objects[i], stopped_object, collided);
        }
    }

    for (GMObject* object : moving_objects)
    {
        if (!collided.count(object))
        {
            object->get_collider()->commit_position();
            object->set_position(object->get_collider()->get_position());;
        }
    }

    for (auto object: collided)
    {
        //TODO: handle collision
    }

    moving_objects.clear();
    stopped_objects.clear();
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
                GMVector tile_global_position = renderer_global_pos + GMVector(c * tile_size, r * tile_size);
                if(camera.is_tile_visible(tile, tile_global_position))
                {
                    GMManager::get_instance()->get_video_service()->draw_tile(tile, tile_global_position, camera_position);
                }
            }
    }
}

void GMMainLoop::track_collision(GMObject* objectA, GMObject* objectB, std::set<GMObject*>& all_collided) {
    if(objectA->get_collider()->collided_with(*(objectB->get_collider())))
    {
        objectA->get_collider()->get_collided_with_others().push_back(objectB->get_collider());
        all_collided.insert(objectA);

        objectB->get_collider()->get_collided_with_others().push_back(objectA->get_collider());
        all_collided.insert(objectB);
    }
}

void GMMainLoop::tick(float delta)
{
    for (GMObject *object : all_objects) {
        object->update(delta);
        enqueue_collider(object);
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