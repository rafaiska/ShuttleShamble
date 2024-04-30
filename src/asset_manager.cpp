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
    for (std::string file_path : file_service->get_file_paths_from_dir(dir_path))
    {
        assets_file->insert_asset(file_path);
    }
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
            file_size += 1;
        }
    }
}

void AssetsFile::insert_asset(std::string asset_path)
{
    if (asset_path.size() > ASSET_PATH_MAX_SIZE)
        throw AssetPathMaxSizeExceeded();
    
    int counter = 0;
    for (char c : asset_path)
    {
        file_handler.write_byte(c);
        counter += 1;
    }

    for (int i = counter; i < ASSET_PATH_MAX_SIZE; ++i)
        file_handler.write_byte(0);
    
    uint32_t end_address_position = file_handler.get_cursor_position();
    file_handler.write_dword(0);
    
    file_handler.write_byte(0); // TODO: ASSET FILE TYPE

    GMFile added_file_handler = GMFile(asset_path, GMFileType::BINARY, GMFileMode::READ);
    added_file_handler.open();
    file_handler.write_bytes_from_file(added_file_handler);
    uint32_t added_file_end = file_handler.get_cursor_position();
    file_handler.seek(end_address_position);
    file_handler.write_dword(added_file_end);

    // CREATE INDEX ENTRY. TODO: MAKE INTO SEPARATE FUNCTION
    uint32_t index = get_index_from_path(asset_path);
}

uint32_t get_index_from_path(std::string path)
{
    XXH32_state_t* state = XXH32_createState();
    XXH32_update(state, path.c_str(), path.size());
    XXH32_hash_t hash = XXH32_digest(state);
    XXH32_freeState(state);
    return ((uint32_t) hash) % MAX_INDEX_ENTRIES;
}
