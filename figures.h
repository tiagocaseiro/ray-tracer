#pragma once

#include <glm/glm.hpp>

struct sphere
{
    sphere(const glm::vec4 _center, const float _radius);
    glm::vec4 center;
    float radius;
};

glm::vec4 normal(const sphere& s, const glm::vec4& p);