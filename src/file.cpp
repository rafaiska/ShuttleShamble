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
    
    if (file_pointer == nullptr)
        throw FileNotOpened();
    
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
    if (file_pointer == nullptr)
        throw FileNotOpened();
    
    fprintf(file_pointer, "%s\n", line.c_str());
}

GMFile& GMFile::operator=(const GMFile &other)
{
    this->path = other.path;
    this->mode = other.mode;
    this->type = other.type;
    return *this;
}
