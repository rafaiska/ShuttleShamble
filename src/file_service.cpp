#include "file_service.hpp"

FileService::FileService()
{
    WORKING_DIR = std::filesystem::current_path();
    std::ostringstream home_dir_str;
    #ifdef _WIN32
    home_dir_str << getenv("HOMEDRIVE") << getenv("HOMEPATH");
    #else
    home_dir_str << getenv("HOME");
    #endif
    HOME_DIR = home_dir_str.str();
}

GMFile &FileService::open_file(std::string file_path, GMFileType type, GMFileMode mode)
{
    opened_files[file_path] = GMFile(file_path, type, mode);
    opened_files[file_path].open();
    if (opened_files[file_path].error())
    {
        opened_files.erase(file_path);
        throw ErrorOpeningFile();
    }
    return opened_files[file_path];
}

void FileService::close_file(std::string file_path)
{
    if (opened_files.count(file_path))
        opened_files.erase(file_path);
}
