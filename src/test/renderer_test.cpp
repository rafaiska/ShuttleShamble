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
    GMSprite* sprite = new GMSprite(2, 2);
    GMImage2D tileset("test.png", 16, 16);
    GMRect rect(8, 8, 0, 0);
    GMTile* tile1 = new GMTile(tileset, rect);
    rect = GMRect(8, 8, 8, 0);
    GMTile* tile2 = new GMTile(tileset, rect);
    rect = GMRect(8, 8, 0, 8);
    GMTile* tile3 = new GMTile(tileset, rect);
    rect = GMRect(8, 8, 8, 8);
    GMTile* tile4 = new GMTile(tileset, rect);
    rect = GMRect(1, 2, 3, 4);
    GMTile* tile5 = new GMTile(tileset, rect);

    sprite->add_tile(tile1);
    sprite->add_tile(tile2);
    sprite->add_tile(tile3);
    sprite->add_tile(tile4);
    ASSERT_THROW(sprite->add_tile(tile5), GMSprite::MaxTilesExceeded);

    ASSERT_EQ(sprite->get_tile(0, 0), tile1);
    ASSERT_EQ(sprite->get_tile(1, 0), tile2);
    ASSERT_EQ(sprite->get_tile(0, 1), tile3);
    ASSERT_EQ(sprite->get_tile(1, 1), tile4);
    ASSERT_THROW(sprite->get_tile(2, 2), GMSprite::TileIndexError);
    ASSERT_THROW(sprite->get_tile(-1, -1), GMSprite::TileIndexError);

    delete sprite;

    ASSERT_EQ(tile1, nullptr);
    ASSERT_EQ(tile2, nullptr);
    ASSERT_EQ(tile3, nullptr);
    ASSERT_EQ(tile4, nullptr);
}