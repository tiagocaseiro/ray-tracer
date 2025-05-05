#pragma once

#pragma warning(disable : 4820)

#include <optional>
#include <vector>

#include "figures.h"
#include "tuple.h"

struct sphere;
struct world;

struct ray
{
    tuple origin    = point();
    tuple direction = vector();
};

struct intersection
{
    float t              = 0.0f;
    const figure* figure = nullptr;
};

struct hit
{
    hit(const intersection& _intersection, const ray& r);
    float t              = 0.0f;
    const figure* figure = nullptr;
    tuple point;
    tuple eye_direction;
    tuple norm;
    bool inside = false;
};

[[nodiscard]] tuple position(const ray& r, const float t);
[[nodiscard]] std::vector<intersection> intersects(const ray& r, const sphere& s);
[[nodiscard]] std::vector<hit> hits(const ray& r, const world& w);

std::ostream& operator<<(std::ostream& os, const ray&);