#pragma once

#include <glm/glm.hpp>

using color = glm::vec4;

namespace colors
{
    inline color WHITE = glm::vec4(1, 1, 1, 1);
    inline color BLACK = glm::vec4(0, 0, 0, 1);
    inline color RED   = glm::vec4(1, 0, 0, 1);
} // namespace colors