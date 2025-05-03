#include "canvas.h"
#include "figures.h"
#include "mat.h"
#include "ray.h"
#include "tuple.h"

int main()
{
    static canvas c = {600, 600};

    static sphere s;

    c.for_each_pixel([](int x, int y) {
        static const auto ray_origin           = make_point(0, 0, -5);
        static const auto wall_z               = 10.f;
        static const auto wall_size            = 7.f;
        static const auto half_wall            = wall_size / 2.0f;
        static const auto canvas_to_wall_ratio = wall_size / static_cast<float>(c.width);

        const auto end_x         = canvas_to_wall_ratio * static_cast<float>(x) - half_wall;
        const auto end_y         = canvas_to_wall_ratio * static_cast<float>(y) - half_wall;
        const auto end_point     = make_point(end_x, end_y, wall_z);
        const auto ray_direction = normalize(end_point - ray_origin);

        const ray r = ray{ray_origin, ray_direction};
        color col   = color::black();
        if(intersects(r, s).empty() == false)
        {
            col = color::red();
        }
        c.paint_pixel(x, y, col);
    });

    c.save_to_file("result");

    return 0;
}