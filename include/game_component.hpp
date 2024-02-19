#ifndef _GAME_COMPONENT_
#define _GAME_COMPONENT_

#include <string>

class GMComponent {
    private:
        std::string name;
    public:
        virtual void update(float delta) = 0;
};

#endif