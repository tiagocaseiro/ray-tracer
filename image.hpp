#pragma once

#include <filesystem>
#include <fstream>

#include "utilities.hpp"

class Image {
  public:
    Image(float _aspect_ratio, uint16_t _width, std::filesystem::path _path)
      : width{_width}, height{static_cast<uint16_t>(_width / _aspect_ratio)}, out(_path) {
        out << "P3\n" << width << " " << height << "\n255\n";
    }
    auto& operator<<(const glm::vec3& color) {
        out << static_cast<int>(color.x) << ' ';
        out << static_cast<int>(color.y) << ' ';
        out << static_cast<int>(color.z) << '\n';
        return *this;
    }
    const uint16_t width;
    const uint16_t height;

  private:
    std::ofstream out;
};
