#pragma once

#include <memory>

#include <glm/glm.hpp>

struct material;

struct sphere
{
    sphere(const glm::vec4& _center, const float _radius, const std::shared_ptr<material>& _mat);

    glm::vec4 center;
    float radius = 0.0f;
    std::shared_ptr<material> mat;
};

glm::vec4 normal(const sphere& s, const glm::vec4& p);