#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>
#include <cmath>

struct GMRect {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;
    GMRect(uint32_t w, uint32_t h, uint32_t x, uint32_t y);
    GMRect() {GMRect(0, 0, 0, 0);}
    GMRect& operator=(const GMRect& lhr);
    bool operator==(const GMRect& lhr) const;
    bool operator!=(const GMRect& lhr) {return !(*this == lhr);}
};

struct GMVector {
    float x;
    float y;
    GMVector(float x, float y) {this->x = x;this->y = y;}
    GMVector() {GMVector(0.0, 0.0);}
    GMVector& operator+(const GMVector& rhs);
    GMVector& operator*(float scalar);
    GMVector& operator=(const GMVector& rhs);
    bool operator==(const GMVector& other) {return this->x == other.x && this->y == other.y;}
};
GMVector& operator*(const float& scalar, GMVector& rhs);

struct GMCircle
{
    GMVector position;
    float radius;
    GMCircle(float x, float y, float r);
    GMCircle(){GMCircle(0, 0, 0);}
    GMCircle& operator=(const GMCircle& other);
};

void get_position_from_rect(const GMRect& rect, GMVector &position);
void set_rect_position(GMRect &rect, const GMVector position);
GMCircle get_aura(const GMRect& r);
float distance_between(const GMVector& vectorA, const GMVector& vectorB);
GMVector center_of_mass(const GMRect& rect);
GMRect rect_intersection(const GMRect& rect_a, const GMRect& rect_b);

#endif