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

bool GMRect::operator==(const GMRect &lhr) const
{
    return this->h == lhr.h && this->w == lhr.w &&
        this->x == lhr.x && this->y == lhr.y;
}

GMVector& operator*(const float& scalar, GMVector& rhs)
{
    return rhs * scalar;
}

void get_position_from_rect(const GMRect& rect, GMVector &position) {
    position.x = (float) rect.x;
    position.y = (float) rect.y;
}

void set_rect_position(GMRect &rect, const GMVector position) {
    rect.x = (uint32_t) position.x;
    rect.y = (uint32_t) position.y;
}

GMCircle get_aura(const GMRect &r)
{
    GMVector center = center_of_mass(r);
    float bigger_edge_size = r.w > r.h ? r.w : r.h;
    float smaller_edge_size = r.w < r.h ? r.w : r.h;
    float inscribed_circle_radius = smaller_edge_size / 2.0;
    float circumscribed_circle_radius = sqrt(bigger_edge_size*bigger_edge_size + smaller_edge_size*smaller_edge_size) / 2.0;
    return GMCircle(center.x, center.y, (inscribed_circle_radius + circumscribed_circle_radius) / 2.0);
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

GMCircle::GMCircle(float x, float y, float r)
{
    position.x = x;
    position.y = y;
    radius = r;
}

GMCircle& GMCircle::operator=(const GMCircle& other)
{
    this->position.x = other.position.x;
    this->position.y = other.position.y;
    this->radius = other.radius;
    return *this;
}