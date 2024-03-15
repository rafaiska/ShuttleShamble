#include "game_object.hpp"

void GMObject::update(float delta)
{
    collider->update(delta);
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

void GMObject::create_collider()
{
    GMVector position = center_of_mass(this->transform);
    float bigger_edge_size = transform.w > transform.h ? transform.w : transform.h;
    float smaller_edge_size = transform.w < transform.h ? transform.w : transform.h;
    float inscribed_circle = smaller_edge_size / 2.0;
    float circumscribed_circle = sqrt(bigger_edge_size*bigger_edge_size + smaller_edge_size*smaller_edge_size) / 2.0;
    collider = new GMCpCollider(position, (inscribed_circle + circumscribed_circle) / 2.0);
}

void GMObject::create_renderer()
{
    renderer = new GMCpRenderer();
}
