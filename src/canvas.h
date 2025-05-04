#pragma once

#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>

#include "tuple.h"

struct canvas
{
    canvas(const int _width, const int _height, const color& default_color = color::black());

    int width;
    int height;

    void paint_pixel(const int col, const int row, const color&);
    void save_to_file(std::filesystem::path);

    void for_each_pixel(std::function<void(int, int)>);

    const color& pixel_at(const int col, const int row);
    const std::vector<color>& get_pixels() const;

private:
    std::vector<color> m_pixels;
};

std::ostream& operator<<(std::ostream& os, const canvas&);