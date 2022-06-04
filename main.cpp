#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>

#include "camera.hpp"
#include "figure.hpp"
#include "ray.hpp"
#include "utilities.hpp"

using World = std::vector<std::unique_ptr<Figure>>;

// Image
constexpr auto aspect_ratio      = 16.f / 9.f;
constexpr auto image_width       = 400;
constexpr auto image_height      = static_cast<int>(image_width / aspect_ratio);
constexpr auto camera            = Camera(aspect_ratio, 2.0f, 1.0f);
constexpr auto tmin              = std::numeric_limits<float>::min();
constexpr auto samples_per_pixel = 100;

auto calculateColor(const Ray& ray) {
    auto direction = glm::normalize(ray.direction);
    auto t         = 0.5f * (direction.y + 1.f); // Normalize to be between 0 and 1
    return glm::mix(glm::vec3{1.0, 1.0, 1.0}, glm::vec3{0.5, 0.7, 1.0}, t);
}

void writeColor(std::ostream& out, const glm::vec3& color) {
    auto r = std::clamp(color.x / float(samples_per_pixel), 0.0f, 0.9999f);
    auto g = std::clamp(color.y / float(samples_per_pixel), 0.0f, 0.9999f);
    auto b = std::clamp(color.z / float(samples_per_pixel), 0.0f, 0.9999f);

    out << static_cast<int>(255.999 * r) << ' ' << static_cast<int>(255.999 * g) << ' '
        << static_cast<int>(255.999 * b) << '\n';
}

auto getColor(const World& world, Ray ray) {
    std::optional<Figure::Hit> hit;
    for (const auto& figure : world) {
        auto tmax = hit ? std::get<2>(*hit) : std::numeric_limits<float>::max();
        if (auto temp = figure->intersects(ray, tmin, tmax)) {
            if (auto t = std::get<2>(*temp); t < tmax)
                hit = temp;
        }
    }
    if (hit) {
        const auto& normal = std::get<1>(*hit);
        return 0.5f * (normal + 1.0f);
    }
    return calculateColor(ray);
}

int main(int, char**) {
    std::ofstream output{"./output.ppm"};
    output << "P3\n" << image_width << " " << image_height << "\n255\n";

    World world;
    world.push_back(std::make_unique<Sphere>(glm::vec3{0, 0, -1}, 0.5f));
    world.push_back(std::make_unique<Sphere>(glm::vec3{0, -100.5, -1}, 100.0f));

    for (auto i = image_height - 1; i >= 0; i--) {
        for (auto j = 0; j < image_width; j++) {
            auto color = glm::vec3();

            for (auto s = 0; s < samples_per_pixel; s++) {
                auto u   = float(j + random<float>()) / (image_width - 1);
                auto v   = float(i + random<float>()) / (image_height - 1);
                auto ray = camera.generate(u, v);
                color += getColor(world, ray);
            }

            writeColor(output, color);
        }
    }
    return 0;
}