#pragma once

struct material
{
    color color     = color::white();
    float ambient   = 0.1f;
    float diffuse   = 0.9f;
    float specular  = 0.9f;
    float shininess = 200.0f;
};