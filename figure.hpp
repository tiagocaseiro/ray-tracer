#pragma once

#include <optional>

#include "ray.hpp"

class Figure {
  public:
    Figure(const glm::vec3& _color) : color{_color} {}
    virtual ~Figure()                                             = default;
    virtual std::optional<float> intersects(const Ray& ray) const = 0;

    const glm::vec3 color;
};

class Sphere : public Figure {
  public:
    Sphere(const glm::vec3& _color, float _radius, const glm::vec3& _center)
      : Figure(_color), radius{_radius}, center{_center} {}

    virtual std::optional<float> intersects(const Ray& ray) const override {
        auto ac           = ray.origin - center;
        auto a            = glm::dot(ray.direction, ray.direction);
        auto half_b       = glm::dot(ray.direction, ac);
        auto c            = glm::dot(ac, ac) - radius * radius;
        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return {};
        auto t1 = (-half_b + std::sqrt(discriminant)) / a;
        auto t2 = (-half_b - std::sqrt(discriminant)) / a;
        return {std::min(t1, t2)};
    }

    const float radius;
    const glm::vec3 center;
};
