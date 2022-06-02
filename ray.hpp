#pragma once

#include <glm/vec3.hpp>

class Ray {
  public:
    Ray(const glm::vec3& _origin, const glm::vec3& _direction)
      : origin{_origin}, direction{_direction} {}

    auto at(float t) const { return origin + t * direction; }

    const glm::vec3 origin;
    const glm::vec3 direction;
};