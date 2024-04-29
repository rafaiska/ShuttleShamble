#include "asset_manager.hpp"

AssetManager::~AssetManager()
{
    if (assets_file != nullptr)
        delete assets_file;
}

AssetsFile *AssetManager::create_assets_file(std::string dir_path, std::string output_path)
{
    assets_file = new AssetsFile(output_path, false);
    assets_file->create_index();
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

void AssetsFile::create_index()
{
    size_t index_entry_size = sizeof(AssetFileIndexEntry);
    for (int j = 0; j < MAX_INDEX_ENTRIES; ++j)
    {
        for (size_t i = 0; i < index_entry_size; ++i)
        {
            file_handler.write_byte(0);
        }
    }
}
