#pragma once


#include "ray.hpp"
#include "utilities.hpp"

#include <glm/trigonometric.hpp>

class Camera {
  public:
    Camera(vec3 look_from, vec3 look_at, vec3 vup, double vfov, double aspect_ratio) {
        auto h               = glm::tan(glm::radians(vfov) / 2.0);
        auto viewport_height = h * 2.0;
        auto viewport_width  = aspect_ratio * viewport_height;
        auto focal_length    = 1.0;

        auto w = glm::normalize(look_from - look_at);
        auto u = glm::normalize(glm::cross(vup, w));
        auto v = glm::cross(w, u);

        origin            = look_from;
        horizontal        = viewport_width * u;
        vertical          = viewport_height * v;
        lower_left_corner = {origin - horizontal / 2.0 - vertical / 2.0 - w};
    }
    Ray generate(double s, double t) const {
        return {origin, lower_left_corner + s * horizontal + t * vertical - origin};
    }


  private:
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;
};