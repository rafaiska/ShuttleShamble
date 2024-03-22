#ifndef _VIDEO_SERVICE_MOCK_H_
#define _VIDEO_SERVICE_MOCK_H_

#include <vector>

#include "tile.hpp"
#include "video_service.hpp"

struct GMDisplayedTile {
    const GMTile* tile;
    GMVector position;
    GMDisplayedTile(const GMTile* tile, const GMVector position) {this->tile = tile; this->position = position;}
};

class VideoServiceMock: public VideoService {
    private:
        std::vector<GMDisplayedTile> displayed_tiles;
    
    public:
        void init(){}
        void exit(){}
        bool draw_tile(const GMTile& tile, const GMVector& position);
        bool clear_canvas();
        uint8_t get_status(){return 0;}
};

#endif