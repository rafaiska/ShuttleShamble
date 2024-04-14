#ifndef _VIDEO_SERVICE_MOCK_H_
#define _VIDEO_SERVICE_MOCK_H_

#include <vector>

#include "tile.hpp"
#include "video_service.hpp"

struct GMDisplayedTile {
    GMTile tile;
    GMVector position;
    GMDisplayedTile(const GMTile tile_, const GMVector position_): tile(tile_), position(position_) {}
};

class VideoServiceMock: public VideoService {
    private:
        std::vector<GMDisplayedTile> displayed_tiles;
    
    public:
        void init(){}
        void exit(){}
        bool draw_tile(const GMTile& tile, const GMVector& tile_position, const GMVector& camera_position);
        bool clear_canvas();
        uint8_t get_status(){return 0;}
        std::vector<GMDisplayedTile> get_displayed_tiles() {return displayed_tiles;}
};

#endif