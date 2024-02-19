#include "game_object.hpp"

void GMObject::update(float delta)
{
    for(GMComponent* c : components) {
        c->update(delta);
    }
}
