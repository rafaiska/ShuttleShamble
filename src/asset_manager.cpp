#include "asset_manager.hpp"

void AssetManager::create_assets_file(std::string dir_path, std::string output_path)
{
    file_handler = file_service->open_file(output_path, GMFileType::BINARY, GMFileMode::WRITE);
    asset_file_path = output_path;
    create_index_space();
    AssetFileIndexEntry entries[MAX_INDEX_ENTRIES];
    for (std::string file_path : file_service->get_file_paths_from_dir(dir_path))
    {
        uint32_t asset_position = insert_asset(file_path);
        create_index_entry(file_path, asset_position, entries);
    }
    for (int position = 0; position < MAX_INDEX_ENTRIES; ++position)
    {
        if(entries[position].address != 0)
            write_index(position, entries[position]);
    }
}

void AssetManager::load_assets_file(std::string file_path)
{
    file_handler = file_service->open_file(file_path, GMFileType::BINARY, GMFileMode::READ);
}

void AssetManager::close_assets_file()
{
    file_service->close_file(asset_file_path);
}

bool AssetManager::check_if_index_position_is_filled(uint32_t index_pos)
{
    file_handler.seek(index_pos * sizeof(AssetFileIndexEntry));
    return (file_handler.read_byte() != 0);
}

bool AssetManager::is_creation_mode()
{
    return (file_handler.is_open() && file_handler.get_mode() != GMFileMode::READ);
}

GMFileCache *AssetManager::load_asset(std::string asset_path)
{
    if (is_creation_mode())
        throw 1; //TODO Exception, assets must not be loaded in creation mode

    if (cached_file_data.count(asset_path) > 0)
        return cached_file_data[asset_path];
    
    uint32_t pos = find_asset_position(asset_path);
    GMFileCache* cache = load_asset_to_cache(asset_path, pos);
    cached_file_data[asset_path] = cache;
    return cache;
}

AssetManager::~AssetManager()
{
    close_assets_file();
    clear_cache();
}

void AssetManager::clear_cache()
{
    if (cached_file_data.size() > 0)
        cached_file_data.clear();
}

uint32_t AssetManager::get_assets_file_size()
{
    return file_handler.get_size();
}

void AssetManager::create_index_space()
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

uint32_t AssetManager::insert_asset(std::string asset_path)
{
    if (asset_path.size() > ASSET_PATH_MAX_SIZE)
        throw AssetPathMaxSizeExceeded();
    
    file_handler.seek_end();
    uint32_t asset_position = file_handler.get_cursor_position();
    int counter = 0;

    file_handler.write_padded_string(asset_path, 0, ASSET_PATH_MAX_SIZE);
    
    uint32_t end_address_position = file_handler.get_cursor_position();
    file_handler.write_dword(0);
    
    file_handler.write_byte(3); // TODO: ASSET FILE TYPE

    GMFile added_file_handler = file_service->open_file(asset_path, GMFileType::BINARY, GMFileMode::READ);
    file_handler.write_bytes_from_file(added_file_handler);
    file_service->close_file(asset_path);

    uint32_t added_file_end = file_handler.get_cursor_position();
    file_handler.seek(end_address_position);
    file_handler.write_dword(added_file_end);

    return asset_position;
}

void AssetManager::create_index_entry(std::string asset_path, uint32_t asset_position, AssetFileIndexEntry* entries)
{
    uint32_t index = get_index_from_path(asset_path);
    uint32_t starting_point = index;
    while (entries[index].address != 0)
    {
        index = (index + 1) % MAX_INDEX_ENTRIES;
        if (index == starting_point)
            throw AssetsFileIndexIsFull();
    }
    for (int i = 0; i < asset_path.size(); ++i)
        entries[index].path[i] = asset_path[i];
    entries[index].address = asset_position;
}

void AssetManager::write_index(uint32_t position, AssetFileIndexEntry &entry)
{
    file_handler.seek(position * sizeof(AssetFileIndexEntry));
    file_handler.write_padded_string(std::string(entry.path), 0, ASSET_PATH_MAX_SIZE);
    file_handler.write_dword(entry.address);
}

uint32_t AssetManager::find_asset_position(std::string asset_path)
{
    uint32_t index = get_index_from_path(asset_path);
    uint32_t starting_index = index;
    uint32_t asset_position = 0;

    while (asset_position == 0)
    {
        file_handler.seek(index * sizeof(AssetFileIndexEntry));
        AssetFileIndexEntry entry = read_index_entry();
        if (std::string(entry.path) == asset_path)
        {
            asset_position = entry.address;
        }
        else
        {
            index = (index + 1) % MAX_INDEX_ENTRIES;
            if (index == starting_index)
                throw AssetNotFoundInFile();
        }
    }
    return asset_position;
}

AssetFileIndexEntry AssetManager::read_index_entry()
{
    AssetFileIndexEntry entry;
    for (int i = 0; i < ASSET_PATH_MAX_SIZE; ++i)
        entry.path[i] = file_handler.read_byte();
    entry.address = file_handler.read_dword();
    return entry;
}

GMFileCache *AssetManager::load_asset_to_cache(std::string path, uint32_t asset_position)
{
    file_handler.seek(asset_position);
    AssetFileRegistryHeader header = read_asset_reg_header();
    uint32_t asset_size = header.end_address - asset_position - sizeof(AssetFileRegistryHeader);
    uint8_t* bytes = new uint8_t[asset_size];
    return new GMFileCache(path, bytes, asset_size);
}

AssetFileRegistryHeader AssetManager::read_asset_reg_header()
{
    AssetFileRegistryHeader header;
    for (int i = 0; i < ASSET_PATH_MAX_SIZE; ++i)
        header.path[i] = file_handler.read_byte();
    header.end_address = file_handler.read_dword();
    header.type = AssetType(file_handler.read_byte());
    return header;
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

GMFileCache::GMFileCache(std::string path_, uint8_t *buffer, uint32_t size_)
{
    path = path_;
    buffer = buffer;
    size = size_;
}

GMFileCache::~GMFileCache()
{
    if (bytes != nullptr)
        delete bytes;
}

AssetFileIndexEntry::AssetFileIndexEntry()
{
    for (int i = 0; i < ASSET_PATH_MAX_SIZE; ++i)
    {
        path[i] = 0;
    }
    address = 0;
}
