#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>
#include <cmath>

struct GMRect {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;
    GMRect(uint32_t w, uint32_t h, uint32_t x, uint32_t y) {this->w = w;this->h = h;this->x = x;this->y = y;}
    GMRect() {GMRect(0, 0, 0, 0);}
};

struct GMVector {
    float x;
    float y;
    GMVector(float x, float y) {this->x = x;this->y = y;}
    GMVector() {GMVector(0.0, 0.0);}
    GMVector& operator+(const GMVector& rhs);
    GMVector& operator*(float scalar);
    GMVector& operator=(const GMVector& rhs);
};

void get_position_from_rect(GMRect rect, GMVector &position);
void set_rect_position(GMRect &rect, GMVector position);
void set_position_to_rect_center(GMVector& position, const GMRect& rect);
float distance_between(const GMVector& vectorA, const GMVector& vectorB);
GMVector center_of_mass(const GMRect& rect);

#endif