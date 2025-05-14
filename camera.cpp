#include "camera.h"

#include "canvas.h"

camera::camera(const canvas& _canvas, const float _fov)
{
    init(_canvas, _fov);
}

void camera::init(const canvas& canvas, const float fov)
{

    const float aspect_ratio = static_cast<float>(canvas.width) / static_cast<float>(canvas.height);

    // Can either represent half_height or half_width, depending on aspect ratio
    const float half_view = std::tan(fov / 2.f);

    if(aspect_ratio > 1)
    {
        half_width  = half_view;
        half_height = half_view / aspect_ratio;
    }
    else
    {
        half_width  = half_view * aspect_ratio;
        half_height = half_view;
    }

    const float view_width = half_width * 2;

    pixel_ratio = view_width / canvas.width;
}
