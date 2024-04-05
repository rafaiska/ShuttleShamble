#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cstdint>
#include <vector>
#include <string>
#include <cmath>

#include "utils.hpp"
#include "cp_collision.hpp"
#include "cp_renderer.hpp"

class GMObject {
    protected:
        uint32_t id;
        GMRect transform;
        std::string last_error;
        GMCpCollider* collider = nullptr;
        GMCpRenderer* renderer = nullptr;
        
    public:
        GMObject(){}
        ~GMObject();
        void update(float delta);
        void set_dimensions(GMVector dimensions);
        void set_position(GMVector new_position);
        std::string get_last_error() {return last_error;}
        void clear_error() {last_error.clear();}
        bool error_detected() {return !last_error.empty();}
        void create_collider();
        GMCpCollider* get_collider() {return collider;}
        void create_renderer();
        GMCpRenderer* get_renderer() {return renderer;}
};

#endif