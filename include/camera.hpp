#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <vector>

#include "utils.hpp"
#include "cp_renderer.hpp"

class GMCamera {
    public:
        GMCamera() {GMCamera(GMRect(0, 0, 0, 0));}
        GMCamera(GMRect rect) {this->transform = rect;}
        void configure(GMRect rect) {this->transform = rect;}
        void set_position(GMVector position) {set_rect_position(this->transform, position);}
        std::vector<GMTile> get_visible_tiles() {return visible_tiles;}
        bool is_renderer_visible(GMCpRenderer& renderer) const;

    private:
        GMRect transform;
        std::vector<GMTile> visible_tiles;
};

#endif