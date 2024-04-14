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
        bool is_tile_visible(GMTile& tile) const;
        GMRect get_transform() const {return transform;}

    private:
        GMRect transform;
};

#endif