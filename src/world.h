#pragma once

#include <memory>
#include <vector>

#include "figures.h"
#include "lighting.h"

struct figure;

struct world
{
    point_light point_light;
    std::vector<sphere> spheres;
};
