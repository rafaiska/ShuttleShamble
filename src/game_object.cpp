#include "game_object.hpp"

void GMObject::update(float delta)
{
    if(collider != nullptr)
        collider->update(delta);
    if(renderer != nullptr)
        renderer->update(delta);
}

GMObject::~GMObject()
{
    if (collider != nullptr)
        delete collider;
}

void GMObject::set_position(GMVector new_position)
{
    if(new_position.x < 0 || new_position.y < 0) {
        last_error = "Trying to set negative coordinates to object";
        return;
    }
    transform.x = (uint32_t) new_position.x;
    transform.y = (uint32_t) new_position.y;
}

void GMObject::set_dimensions(GMVector dimensions) {
    if(dimensions.x < 0 || dimensions.y < 0) {
        last_error = "Trying to set negative dimensions to object";
        return;
    }
    transform.w = (uint32_t) dimensions.x;
    transform.h = (uint32_t) dimensions.y;
}

void GMObject::create_collider(GMVector offset)
{
    GMRect collider_transform = transform;
    collider_transform.x = (uint32_t) offset.x;
    collider_transform.y = (uint32_t) offset.y;
    collider = new GMCpCollider(collider_transform, get_position_from_rect(transform));
}

void GMObject::create_renderer(GMVector offset)
{
    GMRect renderer_transform = transform;
    renderer_transform.x = (uint32_t) offset.x;
    renderer_transform.y = (uint32_t) offset.y;
    renderer = new GMCpRenderer(renderer_transform);
}

GMRect GMObject::get_renderer_global_rect()
{
    if (renderer == nullptr)
        throw NoRendererPresent();
    
    GMRect renderer_global = renderer->get_transform();
    renderer_global.x = renderer_global.x + transform.x;
    renderer_global.y = renderer_global.y + transform.y;

    return renderer_global;
}