#include "material.h"

#include "common.h"
#include "ray.h"

std::optional<scatter> lambertian::on_hit(const ray& r, const hit& h) const
{
    glm::vec4 direction = h.normal + random_unit_vector();

    if(near_zero(direction))
    {
        direction = h.normal;
    }

    const ray scattered     = ray(h.point, direction);
    const color attenuation = albedo;

    return std::make_optional<scatter>(attenuation, scattered);
}

metal::metal(const color& _albedo, const float _fuzz) : albedo(_albedo), fuzz(std::min(_fuzz, 1.0f))
{
}

std::optional<scatter> metal::on_hit(const ray& r, const hit& h) const
{
    glm::vec4 reflected = glm::normalize(reflect(r.direction, h.normal)) + random_unit_vector() * fuzz;
    const ray scattered = ray(h.point, reflected);
    if(glm::dot(scattered.direction, h.normal) < 0)
    {
        return std::nullopt;
    }
    const color attenuation = albedo;

    return std::make_optional<scatter>(attenuation, scattered);
}

lambertian::lambertian(const color& _albedo) : albedo(_albedo)
{
}
