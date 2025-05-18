#pragma once

#include <iostream>
#include <numbers>

#include <glm/glm.hpp>

const float PI = std::numbers::pi;

glm::vec4 point(float x = 0.0f, float y = 0.0f, float z = 0.0f);
glm::vec4 vector(float x = 0.0f, float y = 0.0f, float z = 0.0f);

std::ostream& operator<<(std::ostream& os, const glm::vec4& v);