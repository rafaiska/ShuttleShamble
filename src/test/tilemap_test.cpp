#include <gtest/gtest.h>
#include <algorithm>
#include <set>

#include "data_tree.hpp"
#include "manager.hpp"

class TileMapTest : public testing::Test {
    protected:
        GMManager* manager;

        TileMapTest()
        {
            manager = GMManager::get_instance();
        }

        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(TileMapTest, test_load_from_tiled) {
}