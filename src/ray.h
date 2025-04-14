#pragma once

#pragma warning(disable : 4820)

#include <optional>
#include <vector>

#include "figures.h"
#include "tuple.h"

struct sphere;

struct ray
{
    tuple origin;
    tuple direction;
};

struct intersection
{
    float t              = 0.0f;
    const figure* figure = nullptr;
};

[[nodiscard]] tuple position(const ray& r, const float t);

[[nodiscard]] std::vector<intersection> intersects(const ray& r, const sphere& s);

[[nodiscard]] std::optional<intersection> hit(const std::vector<intersection>& intersections);
