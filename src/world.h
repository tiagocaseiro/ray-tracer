#pragma once

#include <memory>
#include <vector>

#include "figures.h"
#include "lighting.h"

struct figure;

struct world
{
    std::vector<point_light> point_lights;
    std::vector<sphere> spheres;
};
