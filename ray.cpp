#include "ray.h"

glm::vec3 position(const ray& r, const float t)
{
    return r.origin + r.direction * t;
}
