#include "utils.hpp"

GMRect::GMRect(uint32_t w, uint32_t h, uint32_t x, uint32_t y)
{
    this->w = w;
    this->h = h;
    this->x = x;
    this->y = y;
}

GMRect& GMRect::operator=(const GMRect& lhr)
{
    this->w = lhr.w;
    this->h = lhr.h;
    this->x = lhr.x;
    this->y = lhr.y;
    return *this;
}

GMVector& operator*(const float& scalar, GMVector& rhs)
{
    return rhs * scalar;
}

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

GMVector& GMVector::operator+(const GMVector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

GMVector& GMVector::operator*(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

GMVector &GMVector::operator=(const GMVector& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

float distance_between(const GMVector& vectorA, const GMVector& vectorB)
{
    return sqrt((vectorB.x-vectorA.x)*(vectorB.x-vectorA.x) + (vectorB.y-vectorA.y)*(vectorB.y-vectorA.y));
}

GMVector center_of_mass(const GMRect& rect)
{
    GMVector ret;
    ret.x = rect.x + ((float)rect.w / 2.0);
    ret.y = rect.y + ((float)rect.h / 2.0);
    return ret;
}
