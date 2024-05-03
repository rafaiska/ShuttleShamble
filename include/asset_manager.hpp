#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <string>
#include <xxhash.h>

#include "file_service.hpp"

#define MAX_INDEX_ENTRIES 2000
#define ASSET_PATH_MAX_SIZE 40

uint32_t get_index_from_path(std::string path);

class GMFileCache
{
    std::string path;
    uint8_t* bytes=nullptr;
    uint32_t size;

    public:
        GMFileCache(std::string path_, uint8_t* buffer, uint32_t size_);
        ~GMFileCache();
};

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
    std::unordered_map<std::string, GMFileCache*> cached_file_data;

    bool check_if_index_position_is_filled(uint32_t index_pos);

    public:
        AssetsFile(std::string file_path, bool is_read_mode=true, bool is_data_compressed_=false);
        ~AssetsFile();
        size_t get_size() {return file_handler.get_size();}
        void create_index();
        void insert_asset(std::string asset_path);
        void clear_cache();
        void create_and_insert_index_entry(std::string asset_path, uint32_t asset_position);

        class AssetPathMaxSizeExceeded{};
        class AssetsFileIndexIsFull{};
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
        void close_assets_file();
};

#endif