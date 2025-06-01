#include "camera.h"
#include "canvas.h"
#include "color.h"
#include "common.h"
#include "figures.h"
#include "material.h"
#include "ray.h"

color ray_color(const ray& r, const std::vector<sphere>& spheres, const float depth)
{
    if(depth <= 0)
    {
        return colors::BLACK;
    }
    std::optional<hit> h = on_hit(r, spheres, 0.001f, INF);

    if(h == std::nullopt)
    {
        glm::vec4 unit_direction = glm::normalize(r.direction);
        float a                  = 0.5 * (unit_direction.y + 1.0);
        return (1.0f - a) * colors::WHITE + a * color(0.5, 0.7, 1.0, 1.0);
    }

    if(h->sphere.mat == nullptr)
    {
        return colors::BLACK;
    }

    if(const std::optional<scatter> s = h->sphere.mat->on_hit(r, *h))
    {
        return s->attenuation * ray_color(s->ray, spheres, depth - 1);
    }
    return colors::BLACK;
}

glm::vec4 sample_square()
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return point(random_number() - 0.5, random_number() - 0.5, 0);
}

int main()
{
    const float aspect_ratio = 16.f / 9.f;
    const int image_width    = 400;
    const int image_height   = image_width / aspect_ratio;

    const int max_depth = 100;

    const float viewport_height = 2.0;
    const float viewport_width = viewport_height * (static_cast<float>(image_width) / static_cast<float>(image_height));

    const float viewport_width_increment  = viewport_width / image_width;
    const float viewport_height_increment = viewport_height / image_height;

    const float focal_length = 1.0f;

    const int samples_per_pixel = 100;

    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0, 1.0));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5, 1.0));
    auto material_left   = std::make_shared<metal>(color(0.8, 0.8, 0.8, 1.0), 0.3f);
    auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2, 1.0), 1.0f);

    std::vector<sphere> spheres = {{point(0.0, -100.5, -1.0), 100.0, material_ground},
                                   {point(0.0, 0.0, -1.2), 0.5, material_center},
                                   {point(-1.0, 0.0, -1.0), 0.5, material_left},
                                   {point(1.0, 0.0, -1.0), 0.5, material_right}};

    canvas c(image_width, image_height);

    const glm::vec4 camera_center  = point();
    const glm::vec4 viewport_start = point(-viewport_width / 2.f + viewport_width_increment / 2.f,
                                           viewport_height / 2 - viewport_height_increment / 2.f, -focal_length);

    for(auto j = 0; j != image_height; j++)
    {
        for(auto i = 0; i != image_width; i++)
        {
            color col = color(0, 0, 0, 255);
            for(auto l = 0; l != samples_per_pixel; l++)
            {
                glm::vec4 offset      = sample_square();
                glm::vec4 viewport_to = viewport_start;
                viewport_to.x += (i + offset.x) * viewport_width_increment;
                viewport_to.y -= (j + offset.y) * viewport_height_increment;

                ray r = ray(camera_center, viewport_to - camera_center);

                std::optional<float> t_opt = std::nullopt;
                const sphere* s_ptr        = nullptr;

                col += ray_color(r, spheres, max_depth);
            }
            col /= samples_per_pixel;
            c.paint_pixel(i, j, col);
        }
    }

    c.save_to_file("result.ppm");

    return 0;
}