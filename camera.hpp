#pragma once


#include "ray.hpp"
#include "utilities.hpp"

#include <glm/trigonometric.hpp>

class Camera {
  public:
    Camera(
        vec3 look_from,
        vec3 look_at,
        vec3 vup,
        double vfov,
        double aspect_ratio,
        double aperture,
        double focus_distance) {
        auto h               = glm::tan(glm::radians(vfov) / 2.0);
        auto viewport_height = h * 2.0;
        auto viewport_width  = aspect_ratio * viewport_height;
        auto focal_length    = 1.0;

        w = glm::normalize(look_from - look_at);
        u = glm::normalize(glm::cross(vup, w));
        v = glm::cross(w, u);

        lens_radius       = aperture / 2.0;
        origin            = look_from;
        horizontal        = viewport_width * u * focus_distance;
        vertical          = viewport_height * v * focus_distance;
        lower_left_corner = {origin - horizontal / 2.0 - vertical / 2.0 - w * focus_distance};
    }
    Ray generate(double s, double t) const {
        auto rd     = lens_radius * random_in_unit_disk();
        auto offset = u * rd.x + v * rd.y;
        return {
            origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset};
    }


  private:
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 lower_left_corner;
    vec3 w;
    vec3 u;
    vec3 v;
    double lens_radius;
};