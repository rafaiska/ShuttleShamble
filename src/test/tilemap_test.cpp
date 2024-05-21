#include <gtest/gtest.h>
#include <algorithm>
#include <set>

#include "manager.hpp"
#include "tilemap.hpp"

class TileMapTest : public testing::Test {
    protected:
        GMManager* manager;
        FileService* file_service;
        AssetManager* asset_manager;

        TileMapTest()
        {
            manager = GMManager::get_instance();
            file_service = manager->start_file_service();
            asset_manager = manager->start_asset_manager();
        }

        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(TileMapTest, test_load_from_tiled) {
    if (!(file_service->file_exists("test_assets.gma")))
    {
        asset_manager->create_assets_file("src/test/assets", "test_assets.gma");
        asset_manager->close_assets_file();
    }
    asset_manager->load_assets_file("test_assets.gma");
    GMFileCache* cached = asset_manager->load_asset("src/test/assets/TestMap.tmx");
    XMLDocument xml_doc;
    xml_doc.Parse((char*) cached->bytes, cached->size);
    GMTileMap map;
    map.load_tileset_from_tiled_xml(xml_doc);
    map.load_tilemap_from_tiled_xml(xml_doc);
}