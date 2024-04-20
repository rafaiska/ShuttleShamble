#ifndef _FILE_SERVICE_HPP_
#define _FILE_SERVICE_HPP_

#include<string>
#include<unordered_map>

#include "file.hpp"

class FileService
{
    std::string WORKING_DIR;
    std::string HOME_DIR;

    std::unordered_map<std::string, GMFile*> opened_files;

    public:
        ~FileService();
        std::string get_working_dir() {return WORKING_DIR;}
        std::string get_home_dir() {return HOME_DIR;}
        GMFile* get_file(std::string file_path) {return opened_files[file_path];}
        GMFile* open_file(std::string file_path);
        void close_file(std::string file_path);
};

#endif