#pragma once

#include <glm/glm.hpp>

struct canvas;

struct camera
{
    camera(const canvas& c, const float _fov);

    const float pixel_ratio = 1;
    const glm::mat4 transform;
};

static float calculate_pixel_ratio(const canvas& c, const float _fov);