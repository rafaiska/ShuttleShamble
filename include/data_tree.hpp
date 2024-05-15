#ifndef _DATA_TREE_H_
#define _DATA_TREE_H_

#define GMDataTree tinyxml2::XMLDocument

#include <string>
#include <vector>
#include <unordered_map>
#include <tinyxml2.h>

#include "utils.hpp"

void load_from_buffer(GMDataTree& data_tree, uint8_t *buffer, uint32_t buffer_size);

#endif