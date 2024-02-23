#ifndef _CP_HANDLER_H_
#define _CP_HANDLER_H_

#include <string>

#include "game_component.hpp"

class GMCpHandler {
    public:
        virtual std::string handled_component() = 0;
        virtual void enqueue(GMComponent* component) = 0;
        virtual void handle_all() = 0;
};

#endif