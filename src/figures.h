#pragma once

#pragma warning(disable : 4514)

#include "mat.h"
#include "tuple.h"

struct figure
{
    figure(const mat4& _transform = mat4::identity()) : transform(_transform)
    {
    }
    mat4 transform;
};

struct sphere : figure
{
    using figure::figure;

    inline static const tuple centre = make_point();
    inline static const float radius = 1.0f;
};
