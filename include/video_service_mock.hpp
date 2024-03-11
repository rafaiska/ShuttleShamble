#ifndef _VIDEO_SERVICE_MOCK_H_
#define _VIDEO_SERVICE_MOCK_H_

#include <vector>

#include "video_service.hpp"
#include "graphics2d.hpp"

struct DisplayedImage {
    GMImage2D image;
    GMRect src_rect;
    GMRect dst_rect;
    DisplayedImage(GMImage2D image, GMRect src_rect, GMRect dst_rect) {this->image = image; this->src_rect = src_rect; this->dst_rect = dst_rect;}
};

class VideoServiceMock: public VideoService {
    private:
        std::vector<DisplayedImage> displayed_images;
    
    public:
        void init(){}
        void exit(){}
        bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect);
        bool clear_canvas();
        uint8_t get_status(){return 0;}
};

#endif