#ifndef _TILE_H_
#define _TILE_H_

#include <stdint.h>

typedef struct GMTile {
    uint8_t tile_id;
    uint8_t pixels_data[16];
    uint8_t palette_id;
} GMTile;

uint8_t gmtile_get_pixel_value(const GMTile &tile, uint8_t &x, uint8_t &y);
void gmtile_set_pixel_value(GMTile &tile, uint8_t &x, uint8_t &y, uint8_t &value);

#endif