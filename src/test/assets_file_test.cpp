#include <gtest/gtest.h>

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

TEST_F(AssetsFileTest, create_asset_file) {
    AssetsFile* file = asset_manager->create_assets_file("src/test/assets", "test_assets.gma");
//  index                 88000 bytes
//  sample.csv 45 + 118 =   163 bytes
//  sample.png 45 + 640 =   685 bytes
//  sample.xml 45 + 171 =   216 bytes
//                        89064 bytes total
    ASSERT_EQ(file->get_size(), 89064);
}