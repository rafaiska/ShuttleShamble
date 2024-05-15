#ifndef _GM_SCENE_HPP_
#define _GM_SCENE_HPP_

#include <vector>
#include "sprite.hpp"
#include "game_object.hpp"
#include "tilemap.hpp"

class GMScene
{
    GMSprite* background;
    GMTileMap* tilemap;
    std::vector<GMObject*> objects;
};

#endif