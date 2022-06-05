#pragma once

#include <iostream>
#include <random>

using vec3 = glm::vec<3, double, glm::defaultp>;

template <typename T>
T random(double a = 0.0f, double b = 1.0f);

template <>
double random<double>(double a, double b) {
    std::uniform_real_distribution<double> distribution(a, b);
    static std::mt19937 generator;
    return distribution(generator);
}

template <>
vec3 random<vec3>(double a, double b) {
    return {random<double>(a, b), random<double>(a, b), random<double>(a, b)};
}

inline vec3 random_in_unit_sphere() {
    auto p = random<vec3>(-1, 1);
    while (glm::length(p) >= 1)
        p = random<vec3>(-1, 1);
    return p;
}

inline vec3 random_unit_vector() {
    return glm::normalize(random_in_unit_sphere());
}

auto& operator<<(std::ostream& o, const glm::vec3& v) {
    o << v.x << " " << v.y << " " << v.z;
    return o;
}