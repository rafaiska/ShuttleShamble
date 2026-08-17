#include <gtest/gtest.h>

#include "tile.hpp"

void assert_pixel_value(const int &value, const GMTile &tile, const int &x, const int &y);

class TileTest : public testing::Test {
    protected:
        TileTest()
        {
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }
};

TEST_F(TileTest, write_and_read_pixels)
{
    GMTile tile;
    uint8_t value;

    for(uint8_t i=0; i<8; ++i)
        for(uint8_t j=0; j<8; ++j) 
        {
            value = (j*8 + i) % 4;
            gmtile_set_pixel_value(tile, i, j, value);
        }
    
    assert_pixel_value(0, tile, 0, 0);
    assert_pixel_value(3, tile, 7, 7);
    assert_pixel_value(1, tile, 3, 3);
}

void assert_pixel_value(const int &value, const GMTile &tile, const int &x, const int &y)
{
    ASSERT_EQ((uint8_t)value, gmtile_get_pixel_value(tile, (uint8_t)x, (uint8_t)y));
}