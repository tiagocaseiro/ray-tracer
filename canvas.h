#pragma once

#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "color.h"

using pixel_shade_function = std::function<glm::vec3(const glm::vec2&)>;
struct canvas
{
    canvas(const int _width, const int _height, const color& default_color = colors::BLACK);

    void paint_pixel(const int col, const int row, color c);
    void save_to_file(std::filesystem::path);

    const int width;
    const int height;

    friend std::ostream& operator<<(std::ostream& os, const canvas&);

private:
    std::vector<glm::vec3> m_pixels;
};

std::ostream& operator<<(std::ostream& os, const canvas&);