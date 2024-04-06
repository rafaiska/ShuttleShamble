#include <gtest/gtest.h>

#include "cp_collision.hpp"
#include "manager.hpp"
#include "main_loop.hpp"

class RendererTest : public testing::Test {
    protected:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject* obj1;
        GMObject* obj2;

        RendererTest(){}

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();

            obj1 = main_loop.create_object();
            obj1->set_position(GMVector(0, 0));
            obj1->set_dimensions(GMVector(16, 16));
            obj1->create_renderer();
        }

        void TearDown() override {
            main_loop.clear_objects();
        }
};

TEST_F(RendererTest, test_sprite_tiles) {
    GMSprite sprite(2, 2);
    GMImage2D tileset("test.png", 16, 16);

    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 0, 0)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 8, 0)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 0, 8)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 8, 8)));
    ASSERT_THROW(sprite.add_tile(GMTile(tileset, GMRect(1, 2, 3, 4))), GMSprite::MaxTilesExceeded);

    ASSERT_EQ(sprite.get_tile(0, 0), GMTile(tileset, GMRect(8, 8, 0, 0)));
    ASSERT_EQ(sprite.get_tile(1, 0), GMTile(tileset, GMRect(8, 8, 8, 0)));
    ASSERT_EQ(sprite.get_tile(0, 1), GMTile(tileset, GMRect(8, 8, 0, 8)));
    ASSERT_EQ(sprite.get_tile(1, 1), GMTile(tileset, GMRect(8, 8, 8, 8)));
    ASSERT_THROW(sprite.get_tile(2, 2), GMSprite::TileIndexError);
    ASSERT_THROW(sprite.get_tile(-1, -1), GMSprite::TileIndexError);
}