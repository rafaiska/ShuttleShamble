#include "file.hpp"

void GMFile::open()
{
    std::ostringstream flags_os;
    flags_os << (mode == GMFileMode::READ || mode == GMFileMode::BOTH ? "r" : "");
    flags_os << (mode == GMFileMode::WRITE || mode == GMFileMode::BOTH ? "w" : "");
    flags_os << (type == GMFileType::BINARY ? "b" : "");
    std::string flags = flags_os.str();
    file_pointer = fopen(path.c_str(),flags.c_str());
    if (file_pointer == nullptr)
        error_msg = "Error loading file";
}

void GMFile::open(std::string path_, GMFileType type_, GMFileMode mode_)
{
    this->path = path_;
    this->type = type_;
    this->mode = mode_;
    open();
}

void GMFile::close()
{
    if (file_pointer != nullptr)
    {
        fclose(file_pointer);
        file_pointer = nullptr;
    }
}

std::string GMFile::read_line()
{
    if (mode == GMFileMode::WRITE)
        throw WrongFileMode();
    
    check_if_file_opened();
    
    std::ostringstream stream;
    char c = getc(file_pointer);
    while (c != EOF && c != '\n')
    {
        stream << c;
        c = getc(file_pointer);
    }
    return stream.str();
}

void GMFile::write_line(std::string line)
{
    check_if_file_opened();
    
    fprintf(file_pointer, "%s\n", line.c_str());
}

uint8_t GMFile::read_byte()
{
    check_if_file_opened();
    char c = fgetc(file_pointer);
    if (c == EOF && feof(file_pointer))
        throw ReachedEndOfFile();
    return (uint8_t) c;
}

uint32_t GMFile::read_bytes(uint8_t *buffer, uint32_t size)
{
    uint32_t bytes_read = 0;
    for (int i = 0; i < size; ++i)
    {
        try
        {
            buffer[i] = read_byte();
            bytes_read++;
        }
        catch(ReachedEndOfFile e)
        {
            for (int j = i; j < size; ++j)
                buffer[j] = 0;
        }
    }
    return bytes_read;
}

GMFile& GMFile::operator=(const GMFile &other)
{
    this->path = other.path;
    this->mode = other.mode;
    this->type = other.type;
    this->file_pointer = other.file_pointer;
    return *this;
}

uint32_t GMFile::get_cursor_position()
{
    check_if_file_opened();

    return ftell(file_pointer);
}

size_t GMFile::get_size()
{
    check_if_file_opened();
    uint32_t current_position = get_cursor_position();
    fseek(file_pointer, 0, SEEK_END);
    size_t size = get_cursor_position();
    fseek(file_pointer, current_position, SEEK_SET);
    return size;
}

void GMFile::write_bytes_from_file(GMFile &other_file)
{
    check_if_file_opened();
    other_file.check_if_file_opened();

    uint8_t r_byte = 64;
    while(1)
    {
        try
        {
            r_byte = other_file.read_byte();
        }
        catch(ReachedEndOfFile e)
        {
            break;
        }
        write_byte(r_byte);
    }
}

void GMFile::write_padded_string(std::string str, char padding_character, int padded_size)
{
    if (padded_size < str.size())
        throw 1; // TODO: Create Exception
        
    int counter = 0;
    for (char c : str)
    {
        write_byte(c);
        counter += 1;
    }

    for (int i = counter; i < padded_size; ++i)
        write_byte(padding_character);
}

uint32_t GMFile::read_dword()
{
    uint32_t dword = 0;
    for (int i = 3; i >= 0; --i)
    {
        dword = dword << 8;
        dword += read_byte();
    }
    return dword;
}

void GMFile::write_byte(uint8_t byte)
{
    putc(byte, file_pointer);
}

void GMFile::write_dword(uint32_t dword)
{
    for (int i = 3; i >= 0; --i)
    {
        write_byte((dword >> 8 * i) % 256);
    }
}

void GMFile::seek(uint32_t pos)
{
    check_if_file_opened();
    fseek(file_pointer, pos, SEEK_SET);
}

void GMFile::seek_end()
{
    fseek(file_pointer, 0, SEEK_END);
}

void GMFile::check_if_file_opened()
{
    if (file_pointer == nullptr)
        throw FileNotOpened();
}
