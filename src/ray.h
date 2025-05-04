#pragma once

#pragma warning(disable : 4820)

#include <optional>
#include <vector>

#include "figures.h"
#include "tuple.h"

namespace rt
{
    struct sphere;

    struct ray
    {
        tuple origin    = make_point();
        tuple direction = make_vector();
    };

    struct intersection
    {
        float t              = 0.0f;
        const figure* figure = nullptr;
    };

    [[nodiscard]] tuple position(const ray& r, const float t);
    [[nodiscard]] std::vector<intersection> intersects(const ray& r, const sphere& s);
    [[nodiscard]] std::vector<intersection> intersects(const ray& r, std::vector<figure_ptr> figures);
    [[nodiscard]] std::optional<intersection> hit(const std::vector<intersection>& intersections);
} // namespace rt