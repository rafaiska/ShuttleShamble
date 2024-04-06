#include "image.hpp"

bool GMImage2D::operator==(const GMImage2D &other) const
{
    return this->image_path == other.image_path;
}

GMImage2D &GMImage2D::operator=(GMImage2D &other)
{
    this->image_path = other.image_path;
    this->w = other.w;
    this->h = other.h;
    return *this;
}
