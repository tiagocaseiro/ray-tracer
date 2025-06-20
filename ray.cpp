#include "ray.h"

#include "figures.h"

static std::vector<float> hits(const sphere& s, const ray& r)
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
glm::vec4 position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}

std::optional<hit> on_hit(const ray& r, const std::vector<sphere>& spheres, const float t_min, const float t_max)
{
    std::optional<float> t_opt = std::nullopt;
    const sphere* s_ptr        = nullptr;
    for(const sphere& s : spheres)
    {
        for(const float t : hits(s, r))
        {
            if(t > t_max || t < t_min)
            {
                continue;
            }
            if(t_opt == std::nullopt || t < *t_opt)
            {
                t_opt = t;
                s_ptr = &s;
            }
        }
    }

    if(t_opt == std::nullopt || s_ptr == nullptr)
    {
        return std::nullopt;
    }

    const float t   = *t_opt;
    const sphere& s = *s_ptr;

    const glm::vec4 point = position(r, t);

    glm::vec4 norm = normal(s, point);

    // We want the normal to go against ray
    if(glm::dot(norm, r.direction) > 0)
    {
        norm = -norm;
    }

    return hit{s, norm, point};
}

ray::ray(const glm::vec4& _origin, const glm::vec4& _direction) : origin(_origin), direction(glm::normalize(_direction))
{
}
