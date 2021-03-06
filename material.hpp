#pragma once

#include "figure.hpp"
#include "ray.hpp"
#include "utilities.hpp"

#include <glm/geometric.hpp>

struct Scatter {
    Ray ray;
    vec3 attenuation;
};

class Material {
  public:
    ~Material()                                                                  = default;
    virtual std::optional<Scatter> scatter(const Hit& hit, const Ray& ray) const = 0;
};

class Lambertian : public Material {
  public:
    Lambertian(const vec3 _albedo) : albedo{_albedo} {}
    virtual std::optional<Scatter> scatter(const Hit& hit, const Ray& ray) const override {
        auto direction = hit.normal + random_unit_vector();
        if (constexpr auto s = 1e-8;
            std::fabs(direction.x) < s && std::fabs(direction.y) < s && std::fabs(direction.z) < s)
            direction = hit.normal;
        auto scattered = Ray(hit.point, direction);
        return std::make_optional<Scatter>(scattered, albedo);
    }
    const vec3 albedo;
};

class Metal : public Material {
  public:
    Metal(const vec3 _albedo, double _fuzz) : albedo{_albedo}, fuzz{std::min(_fuzz, 1.0)} {}
    virtual std::optional<Scatter> scatter(const Hit& hit, const Ray& ray) const override {
        auto reflected = reflect(ray.direction, hit.normal);
        auto scattered = Ray(hit.point, reflected + fuzz * random_unit_vector());
        return glm::dot(scattered.direction, hit.normal) > 0
            ? std::make_optional<Scatter>(scattered, albedo)
            : std::nullopt;
    }
    const vec3 albedo;
    const double fuzz;
};

class Dielectric : public Material {
  public:
    Dielectric(double _refractive_index) : refractive_index{_refractive_index} {}
    virtual std::optional<Scatter> scatter(const Hit& hit, const Ray& ray) const override {
        auto attenuation = vec3(1.0);
        auto ratio       = hit.front_face ? 1.0 / refractive_index : refractive_index;
        auto cos_theta   = glm::dot(hit.normal, -ray.direction);
        auto sin_theta   = std::sqrt(1 - cos_theta * cos_theta);
        auto direction   = sin_theta > 1.0 || reflectance(cos_theta, ratio) > random<double>()
            ? reflect(ray.direction, hit.normal)
            : refract(hit, ray, ratio);
        return std::make_optional<Scatter>(Ray{hit.point, direction}, attenuation);
    }
    const double refractive_index;

  private:
    static constexpr double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0      = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};