#pragma once

#include <iostream>
#include <random>

using vec3 = glm::vec<3, double, glm::defaultp>;

auto& operator<<(std::ostream& o, const vec3& v) {
    o << v.x << " " << v.y << " " << v.z;
    return o;
}

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

inline auto random_in_unit_sphere() {
    auto p = random<vec3>(-1, 1);
    while (glm::length(p) >= 1)
        p = random<vec3>(-1, 1);
    return p;
}


inline auto random_unit_vector() {
    return glm::normalize(random_in_unit_sphere());
}

auto random_in_unit_disk() {
    auto p = vec3();
    do {
        p = vec3(random<double>(-1, 1), random<double>(-1, 1), 0);
    } while (glm::length(p) >= 1);
    return p;
}

auto reflect(const vec3& direction, const vec3& normal) {
    return direction - 2 * glm::dot(direction, normal) * normal;
}

auto refract(const auto& hit, const auto& ray, double ratio) {
    auto perpendicular =
        ratio * (ray.direction + glm::dot(hit.normal, -ray.direction) * hit.normal);
    auto parallel = -glm::sqrt(std::abs(1.0 - glm::dot(perpendicular, perpendicular))) * hit.normal;
    return perpendicular + parallel;
}