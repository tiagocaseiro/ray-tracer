#pragma once

#include <glm/glm.hpp>

struct ray
{
    const glm::vec3 origin;
    const glm::vec3 direction;
};

[[nodiscard]] glm::vec3 position(const ray& r, const float t);
