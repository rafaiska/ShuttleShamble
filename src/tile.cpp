#include "tile.hpp"

uint8_t gmtile_get_pixel_value(const GMTile &tile, uint8_t &x, uint8_t &y) {
    uint8_t pixel_index = y * 8 + x;
    uint8_t byte_index = pixel_index / 4;
    uint8_t shifts = pixel_index % 4;
    return tile.pixels_data[byte_index] | 3 << shifts;
}

void gmtile_set_pixel_value(GMTile &tile, uint8_t &x, uint8_t &y, uint8_t &value) {
    if (value > 3) return; // Invalid value for 2 bits per pixel bitmap
    uint8_t pixel_index = y * 8 + x;
    uint8_t byte_index = pixel_index / 4;
    uint8_t shifts = pixel_index % 4;
    tile.pixels_data[byte_index] = value << shifts;
}