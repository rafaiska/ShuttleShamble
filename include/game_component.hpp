#ifndef _GAME_COMPONENT_
#define _GAME_COMPONENT_

#include <string>

class GMComponent {
    public:
        virtual std::string get_name() = 0;
        virtual void update(float delta) = 0;
};

#endif