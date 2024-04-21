#include "file.hpp"

void GMFile::open()
{
    if(mode != GMFileMode::WRITE)
    {
        gmf_ifstream.open(path, std::ifstream::in);
        if (!gmf_ifstream.good())
        {
            error_msg = "Couldn't open file";
            return;
        }
    }
    if(mode != GMFileMode::READ)
    {
        gmf_ofstream.open(path, std::ofstream::out);
        if (!gmf_ofstream.good())
        {
            error_msg = "Couldn't open file";
            return;
        }
    }
}

std::string GMFile::read_line()
{
    if (mode == GMFileMode::WRITE)
        throw WrongFileMode();
    
    if (!gmf_ifstream.is_open())
        throw FileNotOpened();
    
    std::ostringstream stream;
    char c = gmf_ifstream.get();
    while (gmf_ifstream.good() && c != '\n')
    {
        stream << c;
        c = gmf_ifstream.get();
    }
    return stream.str();
}

GMFile& GMFile::operator=(const GMFile &other)
{
    this->path = other.path;
    this->mode = other.mode;
    this->type = other.type;
    return *this;
}
