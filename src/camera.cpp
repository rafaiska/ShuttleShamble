#include "camera.hpp"

bool GMCamera::is_tile_visible(GMTile &tile) const
{
    return (rect_intersection(tile.get_boundaries(), this->transform) != GMRect(0,0,0,0));
}
