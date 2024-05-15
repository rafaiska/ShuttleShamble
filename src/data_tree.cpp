#include "data_tree.hpp"

void load_from_buffer(GMDataTree &data_tree, uint8_t *buffer, uint32_t buffer_size)
{
    data_tree.Parse((const char*) buffer, buffer_size);
}
