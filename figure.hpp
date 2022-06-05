#pragma once

#include <optional>
#include <tuple>

#include "ray.hpp"

/**
 * @brief point, normal, t, front face
 *
 */
using Point  = vec3;
using Normal = vec3;
using Hit    = std::tuple<Point, Normal, double, bool>;
class Figure {
  public:
    // Figure(const vec3& _color) : color{_color} {}
    Figure()                                                                              = default;
    virtual ~Figure()                                                                     = default;
    virtual std::optional<Hit> intersects(const Ray& ray, double tmin, double tmax) const = 0;

    // const vec3 color;
};

class Sphere : public Figure {
  public:
    Sphere(
        // const vec3& _color,
        const vec3& _center,
        double _radius)
      : Figure(), radius{_radius}, center{_center} {}

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

        return {std::make_tuple(std::move(point), std::move(normal), t, front_face)};
    }

    const double radius;
    const vec3 center;
};
