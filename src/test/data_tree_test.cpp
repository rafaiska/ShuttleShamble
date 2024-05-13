#include <gtest/gtest.h>

#include "data_tree.hpp"

class DataTreeTest : public testing::Test {
    protected:
        GMDataTree data_tree;

        DataTreeTest(){}

        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(DataTreeTest, insert_nodes_into_tree) {
    data_tree.get_root().insert_child("passoca");
    data_tree.get_root().get_child("passoca").insert_child("amendoim");
    data_tree.get_root().get_child("passoca").get_child("amendoim");
}