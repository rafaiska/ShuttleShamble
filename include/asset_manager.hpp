#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <string>

#include "file_service.hpp"

#define MAX_INDEX_ENTRIES 2000

enum AssetType
{
    XML, PNG, MOD, OTHER
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

class AssetsFile
{
    GMFile file_handler;
    bool is_data_compressed;
    size_t file_size;

    public:
        AssetsFile(std::string file_path, bool is_read_mode=true, bool is_data_compressed_=false);
        ~AssetsFile();
        size_t get_size() {return file_size;}
        void create_index();
};

class AssetManager
{
    private:
        FileService* file_service;
        AssetsFile* assets_file = nullptr;
    public:
        AssetManager(FileService* file_service_): file_service(file_service_){}
        ~AssetManager();
        AssetsFile* create_assets_file(std::string dir_path, std::string output_path);
        AssetsFile* load_assets_file(std::string file_path);
        AssetsFile* get_assets_file() {return assets_file;}
};

#endif