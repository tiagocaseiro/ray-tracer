#pragma once

#include <iostream>
#include <random>

template <typename T>
T random(float a = 0.0f, float b = 1.0f);

template <>
float random<float>(float a, float b) {
    static std::uniform_real_distribution<float> distribution(a, b);
    static std::mt19937 generator;
    return distribution(generator);
}

template <>
glm::vec3 random<glm::vec3>(float a, float b) {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return {random<float>(a, b), random<float>(a, b), random<float>(a, b)};
}

auto& operator<<(std::ostream& o, const glm::vec3& v) {
    o << v.x << " " << v.y << " " << v.z;
    return o;
}