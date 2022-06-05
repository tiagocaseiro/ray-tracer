#pragma once

#include <iostream>
#include <random>

template <typename T = float>
auto random() {
    static std::uniform_real_distribution<T> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

auto& operator<<(std::ostream& o, const glm::vec3& v) {
    o << v.x << " " << v.y << " " << v.z;
    return o;
}