#include "tile.hpp"

GMTile::GMTile(GMImage2D image, GMRect boundaries)
{
    this->image = image;
    this->boundaries = boundaries;
}

void GMTile::set_image(std::string path, uint16_t w, uint16_t h)
{
    this->image.set_path(path);
    this->image.set_dimensions(w, h);
}

void GMTile::set_boundaries(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    this->boundaries.x = x;
    this->boundaries.y = y;
    this->boundaries.w = w;
    this->boundaries.h = h;
}