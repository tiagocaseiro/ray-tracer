#include "ray.h"

glm::vec3 position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}

ray::ray(const glm::vec4& _origin, const glm::vec4& _direction) : origin(_origin), direction(glm::normalize(_direction))
{
}
