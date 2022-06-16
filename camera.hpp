#pragma once


#include "ray.hpp"
#include "utilities.hpp"

class Camera {
  public:
    constexpr Camera(double aspect_ratio, double viewport_height, double focal_length)
      : origin{}, horizontal{viewport_height * aspect_ratio, 0, 0}, vertical{0, viewport_height, 0},
        lower_left_corner{origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focal_length)} {}

    Ray generate(double u, double v) const {
        auto direction = lower_left_corner + u * horizontal + v * vertical - origin;
        return {origin, direction};
    }

    const vec3 origin;
    const vec3 horizontal;
    const vec3 vertical;
    const vec3 lower_left_corner;
};