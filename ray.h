#pragma once

#include <glm/glm.hpp>

struct ray
{
    ray(const glm::vec4& _origin, const glm::vec4& _direction);

    const glm::vec4 origin;
    const glm::vec4 direction;
};

[[nodiscard]] glm::vec3 position(const ray& r, const float t);
