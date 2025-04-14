#pragma once

#pragma warning(disable : 4514)

#include "tuple.h"

struct figure
{
    figure() = default;
};

struct sphere : figure
{
    sphere(const tuple _centre, const float _radius) : figure(), centre(_centre), radius(_radius)
    {
    }

    tuple centre;
    float radius;
};