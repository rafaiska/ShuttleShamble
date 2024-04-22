#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <cstdio>
#include <string>
#include <sstream>

enum GMFileType
{
    BINARY, TEXT
};

enum GMFileMode
{
    READ, WRITE, BOTH
};

class GMFile
{
    FILE* file_pointer=nullptr;
    std::string path;
    GMFileType type;
    GMFileMode mode;
    std::string error_msg;

    public:
        GMFile(){}
        GMFile(std::string path_, GMFileType type_, GMFileMode mode_): path(path_), type(type_), mode(mode_){}
        ~GMFile(){if (file_pointer != nullptr) close();}
        void open();
        void close();
        std::string read_line();
        void write_line(std::string line);
        uint8_t read_byte();
        uint16_t read_word();
        uint32_t read_dword();
        void write_byte(uint8_t byte);
        void write_word(uint16_t word);
        void write_dword(uint16_t dword);
        void seek();
        std::string get_error_msg() {return error_msg;}
        bool error() {return error_msg.size() > 0;}
        void clear_error() {error_msg.clear();}
        GMFile& operator=(const GMFile& other);

        class WrongFileMode {};
        class FileNotOpened {};
};

#endif