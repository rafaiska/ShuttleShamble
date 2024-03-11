#include "video_service_mock.hpp"

bool VideoServiceMock::draw_image(GMImage2D image, GMRect src_rect, GMRect dst_rect)
{
    this->displayed_images.push_back(DisplayedImage(image, src_rect, dst_rect));
    return true;
}

bool VideoServiceMock::clear_canvas()
{
    return true;
}