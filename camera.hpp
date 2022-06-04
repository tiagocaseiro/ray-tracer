#pragma once

#include <glm/vec3.hpp>

#include "ray.hpp"

class Camera {
  public:
    constexpr Camera(float aspect_ratio, float viewport_height, float focal_length)
      : origin{}, horizontal{viewport_height * aspect_ratio, 0, 0}, vertical{0, viewport_height, 0},
        lower_left_corner{
            origin - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length)} {}

    Ray generate(float u, float v) const {
        auto direction = glm::normalize(lower_left_corner + u * horizontal + v * vertical - origin);
        return {origin, direction};
    }

    const glm::vec3 origin;
    const glm::vec3 horizontal;
    const glm::vec3 vertical;
    const glm ::vec3 lower_left_corner;
};