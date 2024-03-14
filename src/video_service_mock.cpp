#include "video_service_mock.hpp"

bool VideoServiceMock::draw_tile(const GMTile& tile, const GMVector& position)
{
    this->displayed_tiles.push_back(GMDisplayedTile(&tile, position));
    return true;
}

bool VideoServiceMock::clear_canvas()
{
    return true;
}