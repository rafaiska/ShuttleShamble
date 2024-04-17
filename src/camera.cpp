#include "camera.hpp"

bool GMCamera::is_tile_visible(const GMTile &tile, const GMVector global_position) const
{
    GMRect tile_rect = tile.get_boundaries();
    tile_rect.x = global_position.x;
    tile_rect.y = global_position.y;
    return (rect_intersection(tile_rect, this->transform) != GMRect(0,0,0,0));
}
