#pragma once

#include <glm/glm.hpp>

struct canvas;

struct camera
{
    camera(const canvas& c, const float _fov);

    float pixel_ratio = 0;
    float half_width  = 0;
    float half_height = 0;
    const glm::mat4 transform;

private:
    void init(const canvas& c, const float _fov);
};

glm::mat4 view_transform();
