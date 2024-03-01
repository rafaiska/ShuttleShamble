#include "utils.hpp"

void get_position_from_rect(GMRect rect, GMVector &position) {
    position.x = (float) rect.x;
    position.y = (float) rect.y;
}

void set_rect_position(GMRect &rect, GMVector position) {
    rect.x = (uint32_t) position.x;
    rect.y = (uint32_t) position.y;
}

void set_position_to_rect_center(GMVector& position, const GMRect& rect) {
    position.x = ((float)(rect.x + rect.w))/2.0;
    position.y = ((float)(rect.y + rect.h))/2.0;
}

GMVector& GMVector::operator+(GMVector const &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

GMVector& GMVector::operator*(float const& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

GMVector &GMVector::operator=(GMVector const &rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}
