#include "asset_manager.hpp"

AssetManager::~AssetManager()
{
    close_assets_file();
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

void AssetManager::close_assets_file()
{
    file_service->close_file(file_handler.get_path());
}

bool AssetManager::check_if_index_position_is_filled(uint32_t index_pos)
{
    file_handler.seek(index_pos * sizeof(AssetFileIndexEntry));
    return (file_handler.read_byte() != 0);
}

void AssetManager::init_file(std::string file_path, bool is_read_mode, bool is_data_compressed_)
{
    GMFileMode mode = is_read_mode ? GMFileMode::READ : GMFileMode::WRITE;
    file_handler.open(file_path, GMFileType::BINARY, mode);
}

AssetManager::~AssetManager()
{
    close_assets_file();
    clear_cache();
}

void AssetManager::clear_cache()
{
    for (auto file_cache_entry: cached_file_data)
    {
        if (file_cache_entry.second != nullptr)
            delete file_cache_entry.second;
    }
    cached_file_data.clear();
}

void AssetManager::create_index()
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

void AssetManager::insert_asset(std::string asset_path)
{
    if (asset_path.size() > ASSET_PATH_MAX_SIZE)
        throw AssetPathMaxSizeExceeded();
    
    file_handler.seek_end();
    uint32_t asset_position = file_handler.get_cursor_position();
    int counter = 0;

    file_handler.write_padded_string(asset_path, 0, ASSET_PATH_MAX_SIZE);
    
    uint32_t end_address_position = file_handler.get_cursor_position();
    file_handler.write_dword(0);
    
    file_handler.write_byte(0); // TODO: ASSET FILE TYPE

    GMFile added_file_handler = GMFile(asset_path, GMFileType::BINARY, GMFileMode::READ);
    added_file_handler.open();
    file_handler.write_bytes_from_file(added_file_handler);
    added_file_handler.close();

    uint32_t added_file_end = file_handler.get_cursor_position();
    file_handler.seek(end_address_position);
    file_handler.write_dword(added_file_end);

    create_and_insert_index_entry(asset_path, asset_position);
}

void AssetsFile::create_and_insert_index_entry(std::string asset_path, uint32_t asset_position)
{
    uint32_t index = get_index_from_path(asset_path);
    uint32_t starting_point = index;
    while (check_if_index_position_is_filled(index))
    {
        index = (index + 1) % MAX_INDEX_ENTRIES;
        if (index == starting_point)
            throw AssetsFileIndexIsFull();
    }
    file_handler.seek(index * sizeof(AssetFileIndexEntry));
    file_handler.write_padded_string(asset_path, 0, ASSET_PATH_MAX_SIZE);
    file_handler.write_dword(asset_position);
}

uint32_t get_index_from_path(std::string path)
{
    XXH64_state_t* state = XXH64_createState();
    if (state == NULL)
        throw 1;
    XXH64_reset(state, 0);
    XXH64_update(state, path.c_str(), path.size());
    XXH64_hash_t hash = XXH64_digest(state);
    XXH64_freeState(state);
    return ((uint32_t) hash) % MAX_INDEX_ENTRIES;
}

GMFileCache::~GMFileCache()
{
    if (bytes != nullptr)
        delete bytes;
}
