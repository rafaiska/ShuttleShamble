#include <gtest/gtest.h>

#include "manager.hpp"
#include "test_utils.hpp"

class AssetsFileTest : public testing::Test {
    protected:
        GMManager* manager;
        FileService* file_service;
        AssetManager* asset_manager;

        AssetsFileTest()
        {
            manager = GMManager::get_instance();
            file_service = manager->start_file_service();
            asset_manager = manager->start_asset_manager();
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
            asset_manager->close_assets_file();
            file_service->close_all();
        }
};

TEST_F(AssetsFileTest, test_get_index_from_path)
{
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.csv"), 1037);
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.png"), 311);
    ASSERT_EQ(get_index_from_path("src/test/assets/sample.xml"), 439);
}

TEST_F(AssetsFileTest, test_asset_file_entry_header)
{
    AssetFileRegistryHeader header;
    header.type_byte = 131;
    ASSERT_EQ(header.get_type(), AssetType::OTHER);
    ASSERT_TRUE(header.is_compressed());

    header.type_byte = 3;
    ASSERT_EQ(header.get_type(), AssetType::OTHER);
    ASSERT_FALSE(header.is_compressed());
}

TEST_F(AssetsFileTest, create_and_load_assets_file)
{
    asset_manager->create_assets_file("src/test/assets", "test_assets.gma");
    ASSERT_TRUE(asset_manager->is_creation_mode());
    asset_manager->close_assets_file();

    asset_manager->load_assets_file("test_assets.gma");
    ASSERT_EQ(asset_manager->get_assets_file_size(), 106809);
    asset_manager->close_assets_file();
}

TEST_F(AssetsFileTest, assess_cached_files)
{
    asset_manager->load_assets_file("test_assets.gma");

    GMFileCache* cached_file1 = asset_manager->load_asset("src/test/assets/sample.xml");
    GMFile file_handler1 = file_service->open_file("src/test/assets/sample.xml", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler1, *cached_file1), 0);

    GMFileCache* cached_file2 = asset_manager->load_asset("src/test/assets/sample.csv");
    GMFile file_handler2 = file_service->open_file("src/test/assets/sample.csv", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler2, *cached_file2), 0);

    GMFileCache* cached_file3 = asset_manager->load_asset("src/test/assets/sample.png");
    GMFile file_handler3 = file_service->open_file("src/test/assets/sample.png", GMFileType::BINARY, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler3, *cached_file3), 0);
}

TEST_F(AssetsFileTest, create_and_load_compressed_assets_file)
{
    asset_manager->set_compressed(true);
    asset_manager->create_assets_file("src/test/assets", "test_assets_compressed.gma");
    asset_manager->close_assets_file();

    asset_manager->load_assets_file("test_assets_compressed.gma");
    ASSERT_EQ(asset_manager->get_assets_file_size(), 90762);

    GMFileCache* cached_file1 = asset_manager->load_asset("src/test/assets/sample.xml");
    GMFile file_handler1 = file_service->open_file("src/test/assets/sample.xml", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler1, *cached_file1), 0);

    GMFileCache* cached_file2 = asset_manager->load_asset("src/test/assets/sample.csv");
    GMFile file_handler2 = file_service->open_file("src/test/assets/sample.csv", GMFileType::TEXT, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler2, *cached_file2), 0);

    GMFileCache* cached_file3 = asset_manager->load_asset("src/test/assets/sample.png");
    GMFile file_handler3 = file_service->open_file("src/test/assets/sample.png", GMFileType::BINARY, GMFileMode::READ);
    ASSERT_EQ(compare_file_and_cached_file(file_handler3, *cached_file3), 0);
}