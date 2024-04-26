#include "asset_manager.hpp"

AssetManager::~AssetManager()
{
    if (assets_file != nullptr)
        delete assets_file;
}

AssetsFile *AssetManager::create_assets_file(std::string dir_path, std::string output_path)
{
    assets_file = new AssetsFile(output_path, false);
    return assets_file;
}

AssetsFile::AssetsFile(std::string file_path, bool is_read_mode, bool is_data_compressed_)
{
    GMFileMode mode = is_read_mode ? GMFileMode::READ : GMFileMode::WRITE;
    file_handler.open(file_path, GMFileType::BINARY, mode);
}

AssetsFile::~AssetsFile()
{
    file_handler.close();
}
