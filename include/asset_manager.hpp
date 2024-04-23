#ifndef _ASSET_MANAGER_HPP_
#define _ASSET_MANAGER_HPP_

#include <string>

class AssetManager
{
    public:
        static void create_asset_file(std::string dir_path, std::string output_path);
};

enum AssetType
{
    XML, PNG, MOD, OTHER
};

class AssetsFile
{

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