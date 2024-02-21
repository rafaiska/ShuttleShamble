#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cstdint>
#include <vector>

#include "utils.hpp"
#include "game_component.hpp"

class GMObject {
    protected:
        uint32_t id;
        GMRect transform;
        std::string last_error;
        std::vector<GMComponent*> components;
        
    public:
        GMObject(){}
        void update(float delta);
        void set_position(GMVector new_position);
        GMComponent* getComponent(std::string name);
        std::string get_last_error() {return last_error;}
        void clear_error() {last_error.clear();}
        bool error_detected() {return !last_error.empty();}
};

#endif