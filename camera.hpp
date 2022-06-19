#pragma once


#include "ray.hpp"
#include "utilities.hpp"

#include <glm/trigonometric.hpp>
class Camera {
  public:
    Camera(double vfov, double aspect_ratio) : origin{} {
        auto theta           = glm::radians(vfov);
        auto viewport_height = glm::tan(theta / 2) * 2.0;
        auto focal_length    = vec3{0, 0, 1};

        vertical          = {0, viewport_height, 0};
        horizontal        = {viewport_height * aspect_ratio, 0, 0};
        lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - focal_length;
    }

    Ray generate(double u, double v) const {
        auto direction = lower_left_corner + u * horizontal + v * vertical - origin;
        return {origin, direction};
    }

  private:
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;
};