#ifndef _DATA_TREE_H_
#define _DATA_TREE_H_

#include <string>
#include <unordered_map>

#include "utils.hpp"

class GMDataTreeNode;

class GMDataTreeNode
{
    std::string name;
    std::string value;
    bool is_root = false;
    std::unordered_map<std::string, GMDataTreeNode> params;
    std::unordered_map<std::string, GMDataTreeNode> children;

    public:
        GMDataTreeNode(std::string name_, std::string value_, bool is_root_): name(name_), value(value_), is_root(is_root_){}
        GMDataTreeNode& get_child(std::string child_name);
        GMDataTreeNode& insert_child(std::string child_name);

        class ChildAlreadyExists : public GMException {public: ChildAlreadyExists(): GMException("Data Tree Node: trying to insert same child twice"){}};
        class ChildNotFound : public GMException {public: ChildNotFound(): GMException("Data Tree Node: child not found"){}};
};

class GMDataTree
{
    GMDataTreeNode root_node = GMDataTreeNode("ROOT", "", true);

    public:
        GMDataTreeNode& get_root() {return root_node;}
        void load_from_xml_data(char* buffer, uint32_t buffer_size);
};

#endif