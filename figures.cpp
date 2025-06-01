#include "figures.h"

#include "material.h"
#include "ray.h"

sphere::sphere(const glm::vec4& _center, const float _radius, const std::shared_ptr<material>& _mat)
    : center(_center), radius(_radius), mat(_mat)
{
}

glm::vec4 normal(const sphere& s, const glm::vec4& p)
{
    return glm::normalize(p - s.center);
}
