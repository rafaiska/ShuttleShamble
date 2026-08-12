#include <gtest/gtest.h>

#include "tile.hpp"

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

TEST_F(FileTest, write_and_read_pixels)
{
    GMTile tile;

    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            gmtile_set_pixel_value(tile, i, j, (j*8 + i) % 4);
    
    ASSERT_EQ(0, gmtile_get_pixel_value(tile, 0, 0));
    ASSERT_EQ(3, gmtile_get_pixel_value(tile, 7, 7));
    ASSERT_EQ(1, gmtile_get_pixel_value(tile, 3, 3));
}