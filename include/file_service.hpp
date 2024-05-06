#ifndef _FILE_SERVICE_HPP_
#define _FILE_SERVICE_HPP_

#include <unordered_map>
#include <vector>
#include <filesystem>

#include "file.hpp"

class FileService
{
    std::string WORKING_DIR;
    std::string HOME_DIR;

    std::unordered_map<std::string, GMFile> opened_files;

    public:
        FileService();
        std::string get_working_dir() {return WORKING_DIR;}
        std::string get_home_dir() {return HOME_DIR;}
        GMFile get_file(std::string file_path);
        GMFile open_file(std::string file_path, GMFileType type, GMFileMode mode);
        void close_file(std::string file_path);
        uint32_t n_files_opened() {return opened_files.size();}
        std::vector<std::string> get_file_paths_from_dir(std::string dir_path);
        void close_all();

        class ErrorOpeningFile{};
        class FileNotOpened{};
        class FileAlreadyOpened{};
};

#endif