#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cstdint>
#include <vector>

#include "utils.hpp"
#include "game_component.hpp"
#include "manager.hpp"

class GMObject {
    protected:
        uint32_t id;
        GMRect transform;
        std::vector<GMComponent*> components;
        
    public:
        void update(float delta);
        void set_position(GMVector new_position);
};

#endif