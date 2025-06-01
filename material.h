#pragma once

#include "color.h"
#include "ray.h"

struct ray;
struct hit;

struct scatter
{
    const color attenuation;
    const ray ray;
};
struct material
{
    virtual ~material() = default;

    virtual std::optional<scatter> on_hit(const ray& r, const hit& rec) const = 0;
};

struct lambertian : material
{
    lambertian(const color& _albedo);
    virtual std::optional<scatter> on_hit(const ray& r, const hit& h) const override;

    const color albedo;
};

struct metal : material
{
    metal(const color& _albedo, const float _fuzz);

    virtual std::optional<scatter> on_hit(const ray& r, const hit& h) const override;

    const color albedo;
    const float fuzz = 1.0f;
};