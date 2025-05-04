#pragma once

#include "tuple.h"

struct sphere;
struct material;
struct figure;

struct point_light
{
    tuple position  = make_point();
    tuple intensity = color::white();
};

tuple normal(const figure* f, tuple point);
tuple reflect(const tuple& in, const tuple& normal);
color shade(const material& material, const point_light& light, const tuple& eye, const tuple& point,
            const tuple& normal);