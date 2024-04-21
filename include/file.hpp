#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <iostream>
#include <fstream>
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
    std::ifstream gmf_ifstream;
    std::ofstream gmf_ofstream;
    std::string path;
    GMFileType type;
    GMFileMode mode;
    std::string error_msg;

    public:
        GMFile(){}
        GMFile(std::string path_, GMFileType type_, GMFileMode mode_): path(path_), type(type_), mode(mode_){}
        void open();
        std::string read_line();
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