#include "canvas.h"

#include <fstream>

canvas::canvas(const int _width, const int _height, const color& default_color)
    : width(_width), height(_height), m_pixels(static_cast<size_t>(_width * _height), default_color)
{
}

float to_gamma(float linear_component)
{
    if(linear_component > 0)
        return std::sqrt(linear_component);

    return 0;
}

glm::vec3 to_pixel_color(glm::vec3 pixel_color)
{
    pixel_color.r = std::clamp(pixel_color.r, 0.0f, 0.99999f) * 256.f;
    pixel_color.g = std::clamp(pixel_color.g, 0.0f, 0.99999f) * 256.f;
    pixel_color.b = std::clamp(pixel_color.b, 0.0f, 0.99999f) * 256.f;

    return pixel_color;
}

void canvas::paint_pixel(const int col, const int row, color c)
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
    for(const glm::vec3& pixel : m_pixels)
    {
        glm::vec3 pixel_color = to_pixel_color(pixel);
        file << pixel_color.r << " " << pixel_color.g << " " << pixel_color.b;

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