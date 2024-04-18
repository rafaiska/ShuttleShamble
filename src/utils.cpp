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

GMVector operator*(const float& scalar, const GMVector& rhs)
{
    return GMVector(rhs.x * scalar, rhs.y*scalar);
}

GMVector get_position_from_rect(const GMRect& rect)
{
    return GMVector((float) rect.x, (float) rect.y);
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

GMVector GMVector::operator+(const GMVector& rhs) const
{
    return GMVector(x + rhs.x, y + rhs.y);
}

GMVector GMVector::operator*(float scalar) const
{
    return GMVector(x * scalar, y * scalar);
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

GMRect rect_intersection(const GMRect &rect_a, const GMRect &rect_b)
{
    int x1 = rect_a.x;
    int y1 = rect_a.y;
    int x2 = rect_a.x + rect_a.w;
    int y2 = rect_a.y + rect_a.h;
    int x3 = rect_b.x;
    int y3 = rect_b.y;
    int x4 = rect_b.x + rect_b.w;
    int y4 = rect_b.y + rect_b.h;

    GMVector bottom_left = GMVector(max(x1, x3), max(y1, y3));
    GMVector top_right = GMVector(min(x2, x4), min(y2, y4));

    if (bottom_left.x > top_right.x || bottom_left.y > top_right.y) {
        return GMRect();
    }
 
    return rect_given_points(top_right, bottom_left);
}

GMRect rect_given_points(GMVector &a, GMVector &b)
{
    int top_right_x = min(a.x, b.x);
    int top_right_y = min(a.y, b.y);
    int w = max(a.x, b.x) - top_right_x;
    int h = max(a.y, b.y) - top_right_y;
    return GMRect(w, h, top_right_x, top_right_y);
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