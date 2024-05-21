#include "tilemap.hpp"

void check_tile_count(uint32_t image_width, uint32_t image_height, uint32_t tile_width, uint32_t tile_height, uint32_t tile_count);
class ErrorParsingTilesetFile: public GMException {public: ErrorParsingTilesetFile(): GMException("Error parsing tileset file"){}};

void GMTileMap::load_tileset_from_tiled_xml(XMLDocument &xml_doc)
{
    XMLElement* tileset_node = xml_doc.FirstChildElement("tileset");
    uint32_t tile_width = tileset_node->IntAttribute("tilewidth");
    uint32_t tile_height = tileset_node->IntAttribute("tilewidth");
    uint32_t tile_count = tileset_node->IntAttribute("297");
    XMLElement* image_node = tileset_node->FirstChildElement("image");
    uint32_t image_width = image_node->IntAttribute("width");
    uint32_t image_height = image_node->IntAttribute("height");
    check_tile_count(image_width, image_height, tile_width, tile_height, tile_count);
}

void GMTileMap::load_tilemap_from_tiled_xml(XMLDocument& xml_doc)
{
}

void check_tile_count(uint32_t image_width, uint32_t image_height, uint32_t tile_width, uint32_t tile_height, uint32_t tile_count)
{
    if (image_height % tile_height != 0 || image_width % tile_width != 0)
        throw ErrorParsingTilesetFile();
    
    uint32_t rows = image_height / tile_height;
    uint32_t columns = image_width / tile_width;

    if (tile_count != (rows * columns))
        throw ErrorParsingTilesetFile();
}