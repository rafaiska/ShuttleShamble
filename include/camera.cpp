#include "camera.hpp"

bool GMCamera::is_renderer_visible(GMCpRenderer &renderer) const
{
    if (!renderer.is_visible())
        return false;
    
    GMRect renderer_transform = renderer.get_transform();
    return (rect_intersection(renderer_transform, this->transform) != nullptr);
}