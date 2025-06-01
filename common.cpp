#pragma once

#include <iostream>
#include <numbers>

#include <glm/glm.hpp>

glm::vec4 point(float x = 0.0f, float y = 0.0f, float z = 0.0f)
{
    return {x, y, z, 1.0f};
}

glm::vec4 vector(float x = 0.0f, float y = 0.0f, float z = 0.0f)
{
    return {x, y, z, 0.0f};
}

std::ostream& operator<<(std::ostream& os, const glm::vec4& v)
{
    os << "x: " << v.x;
    os << " y: " << v.y;
    os << " z: " << v.z;
    os << " w: " << v.w;

    return os;
}

bool near_zero(const glm::vec4 v)
{
    // Return true if the vector is close to zero in all dimensions.
    static constexpr auto s = 1e-8;
    return (std::fabs(v[0]) < s) && (std::fabs(v[1]) < s) && (std::fabs(v[2]) < s);
}

glm::vec4 reflect(const glm::vec4& vector, const glm::vec4& normal)
{

    // Project vector onto normal
    // Negate projection so it points up
    // Add the projection twice to vector
    return vector - 2 * glm::dot(vector, normal) * normal;
}