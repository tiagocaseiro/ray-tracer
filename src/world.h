#pragma once

#include <memory>
#include <vector>

#include "lighting.h"

struct figure;

struct world
{
    point_light point_light;
    std::vector<std::shared_ptr<figure>> figures;
}
