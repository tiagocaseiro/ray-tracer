#include "ray.h"

#include "lighting.h"
#include "mat.h"
#include "world.h"

tuple position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}

std::vector<intersection> intersects(const ray& r1, const sphere& s)
{
    // Transform ray to sphere object space
    ray r = inverse(s.transform) * r1;

    auto sphere_to_ray = r.origin - s.centre;

    auto a = dot(r.direction, r.direction);
    auto b = 2 * dot(r.direction, sphere_to_ray);
    auto c = dot(sphere_to_ray, sphere_to_ray) - 1;

    auto discriminant = b * b - 4 * a * c;

    if(discriminant < 0)
    {
        return {};
    }

    auto t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);

    return {intersection{t0, &s}, intersection{t1, &s}};
}

std::vector<hit> hits(const ray& r, const world& w)
{
    std::vector<hit> hits;

    for(const sphere& s : w.spheres)
    {
        for(const intersection& i : intersects(r, s))
        {
            hits.emplace_back(i, r);
        }
    }

    std::ranges::sort(hits, [](const hit& a, const hit& b) {
        return a.inter.t < b.inter.t;
    });

    return hits;
}

std::optional<intersection> on_hit(const std::vector<intersection>& intersections)
{
    std::optional<intersection> inter;

    for(auto it = std::begin(intersections); it != std::end(intersections); it++)
    {
        if(it->t < 0)
        {
            continue;
        }

        if(inter == std::nullopt || inter->t > it->t)
        {
            inter = *it;
        }
    }

    return inter;
}

hit::hit(const intersection& _inter, const ray& r)
    : inter(_inter),
      point(position(r, _inter.t)),
      eye_direction(-normalize(r.direction)),
      norm(normal(*_inter.figure, point)),
      inside(dot(norm, eye_direction) < 0)
{
    if(inside)
    {
        norm = -norm;
    }
}
