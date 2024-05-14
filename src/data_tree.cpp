#include "data_tree.hpp"

std::vector<GMDataTreeNode *> GMDataTree::all_nodes()
{
    std::vector<GMDataTreeNode *> search_queue;
    int search_queue_cursor = 0;
    search_queue.push_back(get_root());
    while (search_queue_cursor < search_queue.size())
    {
        GMDataTreeNode* current_node = search_queue[search_queue_cursor];
        for (auto pair: current_node->get_children())
        {
            search_queue.push_back(pair.second);
        }
        search_queue_cursor += 1;
    }
    return search_queue;
}

GMDataTree::~GMDataTree()
{
    std::vector<GMDataTreeNode *> nodes = all_nodes();
    while(nodes.size() > 0)
    {
        GMDataTreeNode* n = nodes.back();
        nodes.pop_back();
        delete n;
    }
}

GMDataTreeNode *GMDataTreeNode::get_child(std::string child_name)
{
    if (children.count(child_name) == 0)
        throw ChildNotFound();
    
    return children[child_name];
}

GMDataTreeNode *GMDataTreeNode::insert_child(std::string child_name, std::string value)
{
    if (children.count(child_name) != 0)
        throw ChildAlreadyExists();

    GMDataTreeNode* new_node = new GMDataTreeNode(child_name, value, false);
    children[child_name] = new_node;
    return new_node;
}

void GMDataTreeNode::add_param(std::string name, std::string value)
{
    params[name] = value;
}

std::string GMDataTreeNode::get_param(std::string name)
{
    return params[name];
}
