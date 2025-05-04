#pragma once

#pragma warning(disable : 4514)

#include "mat.h"
#include "material.h"
#include "tuple.h"

struct figure
{
    figure(const material& _material, const mat4& _transform) : mat(_material), transform(_transform)
    {
    }
    explicit figure(const mat4& _transform) : figure(material(), _transform)
    {
    }

    explicit figure(const material& _material) : figure(_material, mat4::identity())
    {
    }

    figure() = default;

    virtual ~figure() = default;

    material mat;
    mat4 transform = mat4::identity();
};

struct sphere : figure
{
    using figure::figure;

    inline static const tuple centre = make_point();
    inline static const float radius = 1.0f;
};
