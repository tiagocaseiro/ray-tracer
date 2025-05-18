#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "common.h"
#include "figures.h"
#include "ray.h"

color ray_color(const ray& r)
{
    float a = 0.5 * (r.direction.y + 1.0);
    return (1.0f - a) * colors::WHITE + a * glm::vec4(0.5, 0.7, 1.0, 1.0);
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

    const float focal_length = 1.0f;

    sphere s1 = sphere(point(0, 0, -1), 0.5f);
    sphere s2 = sphere(point(0, -100.5, -1), 100.f);

    std::vector<sphere> spheres = {s1, s2};

    canvas c(image_width, image_height);

    const glm::vec4 camera_center  = point();
    const glm::vec4 viewport_start = point(-viewport_width / 2.f + viewport_width_increment / 2.f,
                                           viewport_height / 2 - viewport_height_increment / 2.f, -focal_length);

    for(auto j = 0; j != image_height; j++)
    {
        for(auto i = 0; i != image_width; i++)
        {
            glm::vec4 viewport_to = viewport_start;
            viewport_to.y -= j * viewport_height_increment;
            viewport_to.x += i * viewport_width_increment;

            ray r = ray(camera_center, viewport_to - camera_center);

            color col = ray_color(r);

            std::optional<float> t_opt = std::nullopt;
            const sphere* s_ptr        = nullptr;
            for(const sphere& s : spheres)
            {
                for(const float t : hits(s, r))
                {
                    if(t < 0.0f)
                    {
                        continue;
                    }
                    if(t_opt == std::nullopt || t < *t_opt)
                    {
                        t_opt = t;
                        s_ptr = &s;
                    }
                }
            }
            if(t_opt && s_ptr)
            {
                glm::vec4 p = position(r, *t_opt);
                glm::vec4 n = normal(*s_ptr, p);

                col = 0.5f * color(n.x + 1, n.y + 1, n.z + 1, 1.0f);
            }

            c.paint_pixel(i, j, col);
        }
    }
    c.save_to_file("result.ppm");

    return 0;
}