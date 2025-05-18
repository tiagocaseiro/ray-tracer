#include "figures.h"

#include "ray.h"

sphere::sphere(const glm::vec4 _center, const float _radius) : center(_center), radius(_radius)
{
}

glm::vec4 normal(const sphere& s, const glm::vec4& p)
{
    return glm::normalize(p - s.center);
}
