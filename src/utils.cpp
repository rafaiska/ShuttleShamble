#include "utils.hpp"

void get_position_from_rect(GMRect rect, GMVector &position) {
    position.x = (float) rect.x;
    position.y = (float) rect.y;
}

void set_rect_position(GMRect &rect, GMVector position) {
    rect.x = (uint32_t) position.x;
    rect.y = (uint32_t) position.y;
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
