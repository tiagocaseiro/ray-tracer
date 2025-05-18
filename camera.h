#pragma once

#include "common.h"

struct camera
{
    camera(const float _fov);

    const float fov = PI / 4.f;
};