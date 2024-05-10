#include "test_utils.hpp"

/* Returns: n=0 if file and cached file match
            n>0 when n different bytes were found when comparing the two files
            n=-1 size mismatch between file and cached file*/
int compare_file_and_cached_file(GMFile &file, GMFileCache &cached_file)
{
    uint32_t starting_pos = file.get_cursor_position();
    file.seek(0);
    int difference = 0;
    int i = 0;
    uint8_t b;

    while (true)
    {
        try
        {
            b = file.read_byte();
        }
        catch (GMFile::ReachedEndOfFile e)
        {
            if (i != (cached_file.size))
                return -1;
            else
                return difference;
        }

        if (i >= cached_file.size)
        {
            return -1;
        }

        if (b != cached_file.bytes[i])
            difference += 1;
        i += 1;
    }

    file.seek(starting_pos);
    return difference;
}
