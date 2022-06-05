#pragma once

#include <glm/vec3.hpp>

#include "utilities.hpp"

class Ray {
  public:
    Ray(const vec3& _origin, const vec3& _direction) : origin{_origin}, direction{_direction} {}

    auto at(double t) const { return origin + t * direction; }

    const vec3 origin;
    const vec3 direction;
};