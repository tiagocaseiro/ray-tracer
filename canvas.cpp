#include "canvas.h"

#include <fstream>

static size_t color_component_from_1_to_255(float component)
{
    return static_cast<size_t>(std::clamp(component * 255.f, 0.f, 255.f));
}

canvas::canvas(const int _width, const int _height, const color& default_color)
    : width(_width), height(_height), m_pixels(static_cast<size_t>(_width * _height), default_color)
{
}

void canvas::paint_pixel(const int col, const int row, const color& c)
{
    const size_t index = static_cast<size_t>(row * width + col);
    if(index >= m_pixels.size())
    {
        return;
    }
    m_pixels[index] = c;
}

void canvas::save_to_file(std::filesystem::path path)
{
    if(path.has_extension() == false)
    {
        path += ".ppm";
    }

    std::ofstream file{path};
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << 255 << std::endl;
    int i = 0;
    for(auto& pixel : m_pixels)
    {
        file << color_component_from_1_to_255(pixel.r) << " " << color_component_from_1_to_255(pixel.g) << " "
             << color_component_from_1_to_255(pixel.b);
        i++;
        if(i == width)
        {
            i = 0;
            file << std::endl;
        }
        else
        {
            file << " ";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const canvas& canvas)
{
    int i = 0;
    for(auto& pixel : canvas.m_pixels)
    {
        if(i == canvas.width)
        {
            i = 0;
            os << std::endl;
        }
        os << pixel.x << " " << pixel.y << " " << pixel.z;
        i++;
    }
    return os;
}