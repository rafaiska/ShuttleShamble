#include <gtest/gtest.h>

#include "cp_collision.hpp"
#include "manager.hpp"
#include "main_loop.hpp"

void create_sprite(GMObject& object, const GMImage2D& tileset);

class RendererTest : public testing::Test {
    protected:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject* obj1;
        GMImage2D tileset = GMImage2D("test.png", 16, 16);

        RendererTest(){}

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();
            main_loop.configure_camera(GMRect(100, 90, 100, 100));

            obj1 = main_loop.create_object();
            obj1->set_position(GMVector(110, 110));
            obj1->set_dimensions(GMVector(16, 16));
            obj1->create_renderer();
            create_sprite(*obj1, tileset);
        }

        void TearDown() override {
            main_loop.clear_objects();
        }
};

TEST_F(RendererTest, test_sprite_tiles)
{
    GMSprite sprite = obj1->get_renderer()->get_sprite(0);
    ASSERT_THROW(sprite.add_tile(GMTile(tileset, GMRect(1, 2, 3, 4))), GMSprite::MaxTilesExceeded);

    ASSERT_EQ(sprite.get_tile(0, 0), GMTile(tileset, GMRect(8, 8, 0, 0)));
    ASSERT_EQ(sprite.get_tile(1, 0), GMTile(tileset, GMRect(8, 8, 8, 0)));
    ASSERT_EQ(sprite.get_tile(0, 1), GMTile(tileset, GMRect(8, 8, 0, 8)));
    ASSERT_EQ(sprite.get_tile(1, 1), GMTile(tileset, GMRect(8, 8, 8, 8)));
    ASSERT_THROW(sprite.get_tile(2, 2), GMSprite::TileIndexError);
    ASSERT_THROW(sprite.get_tile(-1, -1), GMSprite::TileIndexError);
}

TEST_F(RendererTest, test_display_single_sprite)
{
    main_loop.tick(1.0);
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[0], GMTile(tileset, GMRect(8, 8, 0, 0)));
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[1], GMTile(tileset, GMRect(8, 8, 8, 0)));
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[2], GMTile(tileset, GMRect(8, 8, 0, 8)));
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[3], GMTile(tileset, GMRect(8, 8, 8, 8)));

    obj1->set_position(GMVector(88, 110));
    main_loop.tick(1.0);
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[0], GMTile(tileset, GMRect(8, 8, 0, 8)));
    ASSERT_EQ(main_loop.get_camera().get_visible_tiles()[1], GMTile(tileset, GMRect(8, 8, 8, 8)));

    obj1->set_position(GMVector(84, 110));
    main_loop.tick(1.0);
    ASSERT_TRUE(main_loop.get_camera().get_visible_tiles().size() == 0);
}

void create_sprite(GMObject& object, const GMImage2D& tileset)
{
    GMSprite sprite(2, 2);

    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 0, 0)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 8, 0)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 0, 8)));
    sprite.add_tile(GMTile(tileset, GMRect(8, 8, 8, 8)));
}