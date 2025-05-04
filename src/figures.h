#pragma once

#pragma warning(disable : 4514)

#include "mat.h"
#include "material.h"
#include "tuple.h"

namespace rt
{
    struct figure
    {
        figure(const material& _material, const mat4& _transform) : material(_material), transform(_transform)
        {
        }
        explicit figure(const mat4& _transform) : figure({}, _transform)
        {
        }

        explicit figure(const material& _material) : figure(_material, mat4::identity())
        {
        }

        figure() = default;

        virtual ~figure() = default;

        material material;
        mat4 transform = mat4::identity();
    };

    struct sphere : figure
    {
        using figure::figure;

        inline static const tuple centre = make_point();
        inline static const float radius = 1.0f;
    };

    using figure_ptr = std::shared_ptr<figure>;
} // namespace rt