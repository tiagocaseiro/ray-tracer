#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>

#include "camera.hpp"
#include "figure.hpp"
#include "image.hpp"
#include "ray.hpp"
#include "utilities.hpp"

using World = std::vector<std::unique_ptr<Figure>>;

constexpr auto aspect_ratio      = 16.f / 9.f;
constexpr auto tmin              = std::numeric_limits<float>::min();
constexpr auto samples_per_pixel = 100;

auto calculateColor(const Ray& ray) {
    auto direction = glm::normalize(ray.direction);
    auto t         = 0.5f * (direction.y + 1.f); // Normalize to be between 0 and 1
    return glm::mix(glm::vec3{1.0, 1.0, 1.0}, glm::vec3{0.5, 0.7, 1.0}, t);
}

void writeColor(Image& image, glm::vec3 color) {
    color = {
        255.999 * std::clamp(color.x / float(samples_per_pixel), 0.0f, 0.9999f),
        255.999 * std::clamp(color.y / float(samples_per_pixel), 0.0f, 0.9999f),
        255.999 * std::clamp(color.z / float(samples_per_pixel), 0.0f, 0.9999f)};
    image << color;
}

auto getColor(const World& world, Ray ray) {
    std::optional<Hit> hit;
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
    constexpr auto camera = Camera(aspect_ratio, 2.0f, 1.0f);

    auto image = Image(aspect_ratio, 400, "./output.ppm");
    auto world = World();

    world.push_back(std::make_unique<Sphere>(glm::vec3{0, 0, -1}, 0.5f));
    world.push_back(std::make_unique<Sphere>(glm::vec3{0, -100.5, -1}, 100.0f));

    for (auto i = image.height - 1; i >= 0; i--) {
        for (auto j = 0; j < image.width; j++) {
            auto color = glm::vec3();

            for (auto s = 0; s < samples_per_pixel; s++) {
                auto u   = float(j + random_value()) / (image.width - 1);
                auto v   = float(i + random_value()) / (image.height - 1);
                auto ray = camera.generate(u, v);
                color += getColor(world, ray);
            }

            writeColor(image, color);
        }
    }
    return 0;
}