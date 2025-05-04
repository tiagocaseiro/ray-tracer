#include "canvas.h"
#include "figures.h"
#include "lighting.h"
#include "mat.h"
#include "ray.h"
#include "tuple.h"

int main()
{
    static canvas c = {400, 400};

    static const sphere s = sphere(material(color(1.f, 0.2f, 1.f)));

    static const point_light light = point_light{make_point(-10, 10, -10), color::white()};

    c.for_each_pixel([](int x, int y) {
        static const auto ray_origin           = make_point(0, 0, -5);
        static const auto wall_z               = 10.f;
        static const auto wall_size            = 7.f;
        static const auto half_wall            = wall_size / 2.0f;
        static const auto canvas_to_wall_ratio = wall_size / static_cast<float>(c.width);

        const auto end_x = canvas_to_wall_ratio * static_cast<float>(x) - half_wall;
        const auto end_y = -canvas_to_wall_ratio * static_cast<float>(y) + half_wall;

        const auto end_point     = make_point(end_x, end_y, wall_z);
        const auto ray_direction = normalize(end_point - ray_origin);

        const ray r = ray{ray_origin, ray_direction};

        color col = color::black();
        if(std::optional<intersection> hit_data = hit(intersects(r, s)))
        {
            const tuple hit_point = r.origin + r.direction * hit_data->t;
            const tuple n         = normal(s, hit_point);
            const tuple eye       = -r.direction;

            col = shade(hit_data->figure->material, light, eye, hit_point, n);
        }
        c.paint_pixel(x, y, col);
    });

    c.save_to_file("result");

    return 0;
}