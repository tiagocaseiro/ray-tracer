#pragma once

#include "tuple.h"

struct sphere;

struct point_light
{
    tuple position  = make_point();
    tuple intensity = color::white();
};

tuple normal(const sphere& s, tuple point);
tuple reflect(const tuple& in, const tuple& normal);