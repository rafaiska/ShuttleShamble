#include <gtest/gtest.h>
#include <tinyxml2.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "manager.hpp"

class AssetsFileTest : public testing::Test {
    protected:
        GMManager* manager;
        FileService* file_service;
        AssetManager* asset_manager;

        AssetsFileTest(){}

        void SetUp() override
        {
            manager = GMManager::get_instance();
            file_service = manager->start_file_service();
            asset_manager = manager->start_asset_manager();
        }

        void TearDown() override
        {
            manager->shutdown_asset_manager();
        }
};

TEST_F(AssetsFileTest, test_get_index_from_path)
{
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.csv"), 1037);
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.png"), 311);
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.xml"), 439);
}

TEST_F(AssetsFileTest, create_and_load_assets_file)
{
    asset_manager->create_assets_file("src/test/assets", "test_assets.gma");
    ASSERT_TRUE(asset_manager->is_creation_mode());
    asset_manager->close_assets_file();

    asset_manager->load_assets_file("test_assets.gma");
    ASSERT_EQ(asset_manager->get_assets_file_size(), 88547);
    asset_manager->close_assets_file();
}

TEST_F(AssetsFileTest, load_xml_asset)
{
    asset_manager->load_assets_file("test_assets.gma");
    GMFileCache* cached_file = asset_manager->load_asset("src/test/assets/sample.xml");
    tinyxml2::XMLDocument document;
    document.Parse((char*)cached_file->bytes, (size_t)cached_file->size);
    ASSERT_EQ(std::string(document.FirstChildElement("map")->FirstChildElement("object")->FirstChildElement("name")->GetText()),
        "Passoca");
    ASSERT_EQ(std::string(document.FirstChildElement("map")->FirstChildElement("object")->FirstChildElement("type")->GetText()),
        "Enemy");
    asset_manager->close_assets_file();
}

TEST_F(AssetsFileTest, load_png_asset)
{
    asset_manager->load_assets_file("test_assets.gma");
    GMFileCache* cached_file = asset_manager->load_asset("src/test/assets/sample.png");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* png_surface = IMG_Load((char*)cached_file->bytes);
    ASSERT_NE(png_surface, nullptr);
    SDL_FreeSurface(png_surface);
    SDL_Quit();
    asset_manager->close_assets_file();
}