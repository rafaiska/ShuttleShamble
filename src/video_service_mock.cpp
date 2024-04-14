#include "video_service_mock.hpp"

bool VideoServiceMock::draw_tile(const GMTile& tile, const GMVector& tile_position, const GMVector& camera_position)
{
    this->displayed_tiles.push_back(GMDisplayedTile(tile, tile_position));
    return true;
}

bool VideoServiceMock::clear_canvas()
{
    return true;
}