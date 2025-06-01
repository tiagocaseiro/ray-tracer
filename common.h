#pragma once

#include <iostream>
#include <limits>
#include <numbers>
#include <random>

#include <glm/glm.hpp>

constexpr float PI  = std::numbers::pi_v<float>;
constexpr float INF = std::numeric_limits<float>::infinity();

glm::vec4 point(float x = 0.0f, float y = 0.0f, float z = 0.0f);
glm::vec4 vector(float x = 0.0f, float y = 0.0f, float z = 0.0f);

std::ostream& operator<<(std::ostream& os, const glm::vec4& v);

template <typename T = float>
inline double random_number()
{
    static std::uniform_real_distribution<T> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

template <typename T = float>
inline double random_number(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_number<T>();
}

static glm::vec4 random_vector()
{
    return vector(random_number(), random_number(), random_number());
}

static glm::vec4 random_vector(double min, double max)
{
    return vector(random_number(min, max), random_number(min, max), random_number(min, max));
}

inline glm::vec4 random_unit_vector()
{
    while(true)
    {
        auto p     = random_vector(-1, 1);
        auto lensq = glm::dot(p, p);
        // Dot product is smaller or equal to one if vector is unit or smaller
        // Also check if we're not in danger of underflowing to 0 by squaring really small values.
        if(1e-160 < lensq && lensq <= 1)
            return glm::normalize(p);
    }
}

bool near_zero(const glm::vec4 v);

glm::vec4 reflect(const glm::vec4& vector, glm::vec4& normal);