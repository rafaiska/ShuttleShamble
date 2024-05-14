#include <gtest/gtest.h>
#include <algorithm>
#include <set>

#include "data_tree.hpp"

class DataTreeTest : public testing::Test {
    protected:
        GMDataTree* data_tree;

        DataTreeTest(){}

        void SetUp() override {
            data_tree = new GMDataTree();
        }

        void TearDown() override {
            delete data_tree;
        }
};

TEST_F(DataTreeTest, test_all_nodes) {
    GMDataTreeNode* amendo_node = data_tree->get_root()->insert_child("amendoim_nuts", "AN");
    amendo_node->insert_child("passoca", "PS");
    amendo_node->insert_child("lads_foot", "LF");
    amendo_node->insert_child("quebraquexo", "QQ")->insert_child("caramel", "CM");

    std::set<std::string> node_names;
    for (GMDataTreeNode* node: data_tree->all_nodes())
    {
        node_names.insert(node->get_name());
    }

    ASSERT_EQ(node_names.size(), 6);
    ASSERT_TRUE(node_names.count("ROOT"));
    ASSERT_TRUE(node_names.count("amendoim_nuts"));
    ASSERT_TRUE(node_names.count("passoca"));
    ASSERT_TRUE(node_names.count("lads_foot"));
    ASSERT_TRUE(node_names.count("quebraquexo"));
    ASSERT_TRUE(node_names.count("caramel"));
}

TEST_F(DataTreeTest, insert_nodes_into_tree) {
    data_tree->get_root()->insert_child("passoca", "PS")->insert_child("amendoim", "AD")->add_param("qt", "101");
    GMDataTreeNode* node = data_tree->get_root()->get_child("passoca")->get_child("amendoim");

    ASSERT_EQ(node->get_param("qt"), "101");
}