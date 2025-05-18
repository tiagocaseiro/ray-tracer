#include "ray.h"

#include "figures.h"

glm::vec4 position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}

std::vector<float> hits(const sphere& s, const ray& r)
{
    auto sphere_to_ray = r.origin - s.center;

    // Solving |P - C|^2 - r^2 = 0 <=> |O + tD - C|^2 - r^2 = 0

    auto a = 1; // glm::dot(r.direction, r.direction)
    auto b = 2 * glm::dot(r.direction, sphere_to_ray);
    auto c = glm::dot(sphere_to_ray, sphere_to_ray) - s.radius * s.radius;

    auto discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
    {
        return {};
    }

    auto t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);

    return {t0, t1};
}

ray::ray(const glm::vec4& _origin, const glm::vec4& _direction) : origin(_origin), direction(glm::normalize(_direction))
{
}
