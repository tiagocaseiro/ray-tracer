#include "canvas.h"
#include "color.h"
#include "ray.h"

glm::vec4 ray_color(const ray& r)
{
    float a = 0.5 * (r.direction.y + 1.0);
    return (1.0f - a) * color::WHITE + a * glm::vec4(0.5, 0.7, 1.0, 1.0);
}

glm::vec4 point(float x = 0.0f, float y = 0.0f, float z = 0.0f)
{
    return {x, y, z, 1.0f};
}

glm::vec4 vector(float x = 0.0f, float y = 0.0f, float z = 0.0f)
{
    return {x, y, z, 0.0f};
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& v)
{
    os << "x: " << v.x;
    os << " y: " << v.y;
    os << " z: " << v.z;
    os << " w: " << v.w;

    return os;
}

int main()
{
    const float aspect_ratio = 16.f / 9.f;
    const int image_width    = 400;
    const int image_height   = image_width / aspect_ratio;

    const float viewport_height = 2.0;
    const float viewport_width = viewport_height * (static_cast<float>(image_width) / static_cast<float>(image_height));

    const float viewport_width_increment  = viewport_width / image_width;
    const float viewport_height_increment = viewport_height / image_height;

    canvas c(image_width, image_height);

    const glm::vec4 camera_center  = point();
    const glm::vec4 viewport_start = point(-viewport_width / 2.f + viewport_width_increment / 2.f,
                                           viewport_height / 2 - viewport_height_increment / 2.f, -1);

    for(auto j = 0; j != image_height; j++)
    {
        for(auto i = 0; i != image_width; i++)
        {
            glm::vec4 viewport_to = viewport_start;
            viewport_to.y -= j * viewport_height_increment;
            viewport_to.x += i * viewport_width_increment;

            ray r = ray(camera_center, viewport_to - camera_center);
            c.paint_pixel(i, j, ray_color(r));
        }
    }
    c.save_to_file("result.ppm");

    return 0;
}