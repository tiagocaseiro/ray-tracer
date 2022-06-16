#pragma once

#include <functional>
#include <optional>
#include <tuple>

#include "ray.hpp"

class Material;

struct Hit {
    vec3 point;
    vec3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> material;
};

class Figure {
  public:
    Figure(std::shared_ptr<Material> _material) : material{std::move(_material)} {}
    virtual ~Figure()                                                                     = default;
    virtual std::optional<Hit> intersects(const Ray& ray, double tmin, double tmax) const = 0;

    const std::shared_ptr<Material> material;
};

class Sphere : public Figure {
  public:
    Sphere(const vec3& _center, double _radius, std::shared_ptr<Material> _material)
      : Figure(std::move(_material)), radius{_radius}, center{_center} {}

    virtual std::optional<Hit> intersects(const Ray& ray, double tmin, double tmax) const override {
        auto ac           = ray.origin - center;
        auto a            = glm::dot(ray.direction, ray.direction);
        auto half_b       = glm::dot(ray.direction, ac);
        auto c            = glm::dot(ac, ac) - radius * radius;
        auto discriminant = half_b * half_b - a * c;

        if (discriminant < 0)
            return std::nullopt;

        auto t = (-half_b - std::sqrt(discriminant)) / a;
        if (t < tmin || t > tmax) {
            t = (-half_b + std::sqrt(discriminant)) / a;
            if (t < tmin || t > tmax)
                return std::nullopt;
        }

        auto point      = ray.at(t);
        auto normal     = glm::normalize(point - center);
        auto front_face = glm::dot(normal, ray.direction) < 0;
        if (!front_face)
            normal = -normal;

        return std::make_optional<Hit>(
            std::move(point), std::move(normal), t, front_face, material);
    }

    const double radius;
    const vec3 center;
};
