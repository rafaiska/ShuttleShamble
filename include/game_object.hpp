#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <cstdint>

class GMObject {
    protected:
        uint32_t id;
    public:
        virtual void update(float delta) = 0;
};

#endif