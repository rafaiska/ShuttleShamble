#ifndef _VIDEO_SERVICE_MOCK_H_
#define _VIDEO_SERVICE_MOCK_H_

#include "video_service.hpp"

class VideoServiceMock: public VideoService {
    public:
        void init(){}
        virtual void exit(){}
        virtual bool draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect){return true;}
        virtual bool clear_canvas(){return true;}
        virtual uint8_t get_status(){return 0;}
};

#endif