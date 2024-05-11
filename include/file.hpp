#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <cstdio>
#include <string>
#include <sstream>
#include <cstdint>

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
    FILE* file_pointer = nullptr;
    std::string path;
    GMFileType type;
    GMFileMode mode;
    std::string error_msg;

    void check_if_file_opened();

    public:
        GMFile(){}
        GMFile(std::string path_, GMFileType type_, GMFileMode mode_): path(path_), type(type_), mode(mode_){}
        void open();
        void open(std::string path_, GMFileType type_, GMFileMode mode_);
        void close();
        std::string read_line();
        void write_line(std::string line);
        uint8_t read_byte();
        uint32_t read_bytes(uint8_t* buffer, uint32_t size);
        uint16_t read_word();
        uint32_t read_dword();
        void write_byte(uint8_t byte);
        void write_word(uint16_t word);
        void write_dword(uint32_t dword);
        void seek(uint32_t pos);
        void seek_end();
        std::string get_error_msg() {return error_msg;}
        bool error() {return error_msg.size() > 0;}
        void clear_error() {error_msg.clear();}
        GMFile& operator=(const GMFile& other);
        uint32_t get_cursor_position();
        size_t get_size();
        void write_bytes_from_file(GMFile& other_file);
        void write_padded_string(std::string str, char padding_character, int padded_size);
        GMFileMode get_mode() {return mode;}
        bool is_open() {return (file_pointer != nullptr);}

        class WrongFileMode {};
        class FileNotOpened {};
        class ReachedEndOfFile {};
};

#endif
