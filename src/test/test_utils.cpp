#include "test_utils.hpp"

int compare_file_and_cached_file(GMFile &file, GMFileCache &cached_file)
{
    uint32_t starting_pos = file.get_cursor_position();
    file.seek(0);
    int difference = 0;

    for (int i = 0; i < cached_file.size; ++i)
    {
        try
        {
            difference += file.read_byte() == cached_file.bytes[i] ? 1 : 0;
        }
        catch (GMFile::ReachedEndOfFile e)
        {
            if (i != (cached_file.size - 1))
                difference = -1;
            break;
        }
    }

    file.seek(starting_pos);
    return difference;
}
