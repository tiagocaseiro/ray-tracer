#include "ray.h"

tuple position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}

std::vector<intersection> intersects(const ray& r, const sphere& s)
{
    const tuple l = s.centre - r.origin;

    // Projection of L onto direction of ray
    const float tca = dot(r.direction, l);

    // Completes the triangle of d, l and tca
    auto d = std::sqrt(length(l) * length(l) - tca * tca);

    if(d < 0 || d > s.radius)
    {
        // There was an error calculating d or the sphere has been completely missed
        return {};
    }

    // Absolute distance between the middle point between both intersections
    const float thc = std::sqrt(s.radius * s.radius - d * d);

    const float t0 = tca - thc;
    const float t1 = tca + thc;

    const auto int0 = intersection{t0, &s};
    const auto int1 = intersection{t1, &s};

    return {int0, int1};
}

std::optional<intersection> hit(const std::vector<intersection>& intersections)
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
