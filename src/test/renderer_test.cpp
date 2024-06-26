#include <gtest/gtest.h>

#include <algorithm>

#include "manager.hpp"
#include "main_loop.hpp"

class RendererTest : public testing::Test {
    protected:
        GMManager* manager;
        GMMainLoop main_loop;
        GMObject* obj1;
        VideoServiceMock* video_service;

        GMImage2D tileset = GMImage2D("test.png", 16, 16);
        GMTile tile00 = GMTile(tileset, GMRect(8, 8, 0, 0));
        GMTile tile01 = GMTile(tileset, GMRect(8, 8, 8, 0));
        GMTile tile10 = GMTile(tileset, GMRect(8, 8, 0, 8));
        GMTile tile11 = GMTile(tileset, GMRect(8, 8, 8, 8));
        GMSprite sprite = GMSprite(2, 2, 8);

        RendererTest()
        {
            sprite.add_tile(tile00);
            sprite.add_tile(tile01);
            sprite.add_tile(tile10);
            sprite.add_tile(tile11);
        }

        void SetUp() override {
            manager = GMManager::get_instance();
            main_loop = GMMainLoop();

            manager->start_test_services();
            video_service = (VideoServiceMock*) manager->get_video_service();

            main_loop.configure_camera(GMRect(100, 90, 100, 100));

            obj1 = main_loop.create_object();
            obj1->set_position(GMVector(110, 110));
            obj1->set_dimensions(GMVector(16, 16));
            obj1->create_renderer(GMVector());

            obj1->get_renderer()->add_sprite(sprite);
            obj1->get_renderer()->toggle_visible(true);
        }

        void TearDown() override {
            main_loop.clear_objects();
        }
};

TEST_F(RendererTest, test_sprite_tiles)
{
    GMSprite sprite = obj1->get_renderer()->get_current_sprite();
    ASSERT_THROW(sprite.add_tile(GMTile(tileset, GMRect(8, 8, 9, 10))), GMSprite::MaxTilesExceeded);

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
    std::vector<GMDisplayedTile> visible_tiles = video_service->get_displayed_tiles();
    ASSERT_EQ(visible_tiles.size(), 4);
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile00, GMVector(110, 110))) != visible_tiles.end());
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile01, GMVector(118, 110))) != visible_tiles.end());
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile10, GMVector(110, 118))) != visible_tiles.end());
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile11, GMVector(118, 118))) != visible_tiles.end());
    video_service->clear_displayed_tiles();

    obj1->set_position(GMVector(88, 110));
    main_loop.tick(1.0);
    visible_tiles = video_service->get_displayed_tiles();
    ASSERT_EQ(visible_tiles.size(), 2);
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile01, GMVector(96, 110))) != visible_tiles.end());
    ASSERT_TRUE(std::find(visible_tiles.begin(), visible_tiles.end(), GMDisplayedTile(tile11, GMVector(96, 118))) != visible_tiles.end());
    video_service->clear_displayed_tiles();

    obj1->set_position(GMVector(83, 110));
    main_loop.tick(1.0);
    visible_tiles = video_service->get_displayed_tiles();
    ASSERT_EQ(visible_tiles.size(), 0);
}