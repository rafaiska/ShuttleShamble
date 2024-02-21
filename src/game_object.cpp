#include "game_object.hpp"

void GMObject::update(float delta)
{
    for(GMComponent* c : components) {
        c->update(delta);
    }
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

GMComponent *GMObject::getComponent(std::string name)
{
    for (GMComponent* c : components) {
        if (c->get_name() == name) {
            return c;
        }
    }
    return nullptr;
}
