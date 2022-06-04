#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>

#include "figure.hpp"
#include "ray.hpp"

using World = std::vector<std::unique_ptr<Figure>>;

// Image
constexpr auto aspect_ratio = 16.f / 9.f;
constexpr auto image_width  = 400;
constexpr auto image_height = static_cast<int>(image_width / aspect_ratio);

// Camera
constexpr auto viewport_height = 2.f;
constexpr auto viewport_width  = viewport_height * aspect_ratio;
constexpr auto focal_length    = 1.0f;

constexpr auto origin     = glm::vec3();
constexpr auto horizontal = glm::vec3(viewport_width, 0, 0);
constexpr auto vertical   = glm::vec3(0, viewport_height, 0);
constexpr auto lower_left_corner =
    origin - horizontal / 2.f - vertical / 2.f - glm::vec3(0, 0, focal_length);

auto calculateColor(const Ray& ray) {
    auto direction = glm::normalize(ray.direction);
    auto t         = 0.5f * (direction.y + 1.f); // Normalize to be between 0 and 1
    return glm::mix(glm::vec3{1.0, 1.0, 1.0}, glm::vec3{0.5, 0.7, 1.0}, t);
}

void write(std::ostream& out, const glm::vec3& color) {
    out << static_cast<int>(255.999 * color.x) << ' ' << static_cast<int>(255.999 * color.y) << ' '
        << static_cast<int>(255.999 * color.z) << '\n';
}

int main(int, char**) {
    constexpr auto tmin = std::numeric_limits<float>::min();

    std::ofstream output{"./output.ppm"};
    output << "P3\n" << image_width << " " << image_height << "\n255\n";

    World figures;
    figures.push_back(std::make_unique<Sphere>(glm::vec3{0, 0, -1}, 0.5f));
    figures.push_back(std::make_unique<Sphere>(glm::vec3{0, -100.5, -1}, 100.0f));

    for (auto i = image_height - 1; i >= 0; i--) {
        for (auto j = 0; j < image_width; j++) {
            auto u   = float(j) / (image_width - 1);
            auto v   = float(i) / (image_height - 1);
            auto ray = Ray(
                origin, glm::normalize(lower_left_corner + u * horizontal + v * vertical - origin));
            auto hit = std::optional<Figure::Hit>();

            for (const auto& figure : figures) {
                auto tmax = hit ? std::get<2>(*hit) : std::numeric_limits<float>::max();
                if (auto temp = figure->intersects(ray, tmin, tmax)) {
                    if (auto t = std::get<2>(*temp); t < tmax)
                        hit = temp;
                }
            }

            if (hit) {
                const auto& normal = std::get<1>(*hit);
                auto color         = 0.5f * (normal + 1.0f);
                write(output, color);
            } else {
                auto color = calculateColor(ray);
                write(output, color);
            }
        }
    }
    return 0;
}