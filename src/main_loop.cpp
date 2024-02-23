#include "main_loop.hpp"

void GMMainLoop::tick(float delta)
{
    for (GMObject *object : GMManager::get_instance()->get_objects()) {
        object->update(delta);
        for (GMComponent *component : object->get_components()) {
            if (GMManager::get_instance()->get_handler(component->get_name()) != nullptr)
                GMManager::get_instance()->get_handler(component->get_name())->enqueue(component);
        }
    }
}

void GMMainLoop::main_loop()
{
    while (true)
    {
        tick(1.0);
    }
}