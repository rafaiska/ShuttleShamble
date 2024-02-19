#include "main_loop.hpp"

void GMMainLoop::tick(float delta)
{
}

void GMMainLoop::main_loop()
{
    while (true)
    {
        tick(1.0);
    }
}