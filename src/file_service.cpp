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

GMFile FileService::get_file(std::string file_path)
{
    if (opened_files.count(file_path) == 0)
        throw FileNotOpened();
    return opened_files[file_path];
}

GMFile FileService::open_file(std::string file_path, GMFileType type, GMFileMode mode)
{
    if (opened_files.count(file_path) != 0)
        throw FileAlreadyOpened();
    
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
    {
        opened_files[file_path].close();
        opened_files.erase(file_path);
    }
}

std::vector<std::string> FileService::get_file_paths_from_dir(std::string dir_path)
{
    std::vector<std::string> ret;

    for (auto file: std::filesystem::recursive_directory_iterator(dir_path))
    {
        ret.push_back(file.path());
    }

    return ret;
}

void FileService::close_all()
{
    for (auto f: opened_files)
    {
        f.second.close();
    }
    opened_files.clear();
}
