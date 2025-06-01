#pragma once

#include <memory>
#include <optional>

#include <glm/glm.hpp>

struct sphere;
struct material;

struct ray
{
    ray(const glm::vec4& _origin, const glm::vec4& _direction);

    const glm::vec4 origin;
    const glm::vec4 direction;
};

struct hit
{
    const sphere& sphere;
    const glm::vec4 normal;
    const glm::vec4 point;
};

[[nodiscard]] glm::vec4 position(const ray& r, const float t);
std::optional<hit> on_hit(const ray& r, const std::vector<sphere>& spheres, const float t_min, const float t_max);
