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
        GMManager::get_instance()->log_error(this, "Trying to set negative coordinates to object");
    }
    transform.x = (uint32_t) new_position.x;
    transform.y = (uint32_t) new_position.y;
}
