#include <gtest/gtest.h>
#include <algorithm>
#include <set>

#include "data_tree.hpp"
#include "manager.hpp"

class DataTreeTest : public testing::Test {
    protected:
        GMDataTree* data_tree;
        GMManager* manager;

        DataTreeTest()
        {
            manager = GMManager::get_instance();
        }

        void SetUp() override {
            data_tree = new GMDataTree();
        }

        void TearDown() override {
            delete data_tree;
        }
};

TEST_F(DataTreeTest, test_load_from_xml) {
    manager->start_file_service();
    AssetManager* a_manager = manager->start_asset_manager();
    a_manager->create_assets_file("src/test/assets", "test_assets.gma");
    a_manager->close_assets_file();
    a_manager->load_assets_file("test_assets.gma");
    GMFileCache* cached = a_manager->load_asset("src/test/assets/sample.xml");
    load_from_buffer(*data_tree, cached->bytes, cached->size);
    ASSERT_EQ(std::string(data_tree->FirstChildElement("map")->Attribute("id")), "1");
    ASSERT_EQ(std::string(data_tree->FirstChildElement("map")->FirstChildElement("object")->Attribute("id")), "1912");
    a_manager->close_assets_file();
}