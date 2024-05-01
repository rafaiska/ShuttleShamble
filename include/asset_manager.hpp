#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <string>
#include <xxhash.h>

#include "file_service.hpp"

#define MAX_INDEX_ENTRIES 2000
#define ASSET_PATH_MAX_SIZE 40

uint32_t get_index_from_path(std::string path);

enum AssetType
{
    XML, PNG, MOD, OTHER
};

struct AssetFileIndexEntry
{
    char path[ASSET_PATH_MAX_SIZE];
    uint32_t address;
};

struct AssetFileRegistry
{
    char path[ASSET_PATH_MAX_SIZE];
    uint32_t end_address;
    AssetType type;
};

class AssetsFile
{
    GMFile file_handler;
    bool is_data_compressed;

    public:
        AssetsFile(std::string file_path, bool is_read_mode=true, bool is_data_compressed_=false);
        ~AssetsFile();
        size_t get_size() {return file_handler.get_size();}
        void create_index();
        void insert_asset(std::string asset_path);

        class AssetPathMaxSizeExceeded{};
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