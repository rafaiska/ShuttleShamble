#ifndef _SCENE_LOADER_HPP_
#define _SCENE_LOADER_HPP_

#include "scene.hpp"
#include "asset_manager.hpp"

class SceneLoader
{
    GMScene* loaded_scene = nullptr;
    AssetManager* asset_manager;

    public:
        SceneLoader(AssetManager* asset_manager_): asset_manager(asset_manager_){}
        void create_new_scene();
        void load_tilemap_from_path(std::string path);
};

#endif