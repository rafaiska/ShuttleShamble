#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <string>

#include "file_service.hpp"

class AssetManager
{
    private:
        FileService* file_service;
        AssetsFile* assets_file;
    public:
        AssetManager(FileService* file_service_): file_service(file_service_){}
        ~AssetManager();
        AssetsFile* create_assets_file(std::string dir_path, std::string output_path);
        AssetsFile* load_assets_file(std::string file_path);
        AssetsFile* get_assets_file() {return assets_file;}
};

enum AssetType
{
    XML, PNG, MOD, OTHER
};

class AssetsFile
{
    GMFile file_handler;

    public:
        AssetsFile(std::string file_path);
};

struct AssetFileIndexEntry
{
    char path[40];
    uint32_t address;
};

struct AssetFileRegistry
{
    char path[40];
    uint32_t end_address;
    AssetType type;
};

#endif