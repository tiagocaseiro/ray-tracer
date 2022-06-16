#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>

#include "camera.hpp"
#include "figure.hpp"
#include "image.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "utilities.hpp"

using World = std::vector<std::unique_ptr<Figure>>;

constexpr auto aspect_ratio      = 16.0 / 9.0;
constexpr auto tmin              = 0.001;
constexpr auto samples_per_pixel = 100;
constexpr auto depth             = 50;
constexpr auto scale             = 1.0 / samples_per_pixel;

auto calculateColor(const Ray& ray) {
    auto t = 0.5 * (ray.direction.y + 1.0); // Normalize to be between 0 and 1
    return glm::mix(vec3{1.0, 1.0, 1.0}, vec3{0.5, 0.7, 1.0}, t);
}

void writeColor(Image& image, vec3 color) {
    color *= scale;                         // Average it by dividing by number of samples
    color = glm::sqrt(color);               // Apply gamma 2.0
    color = glm::clamp(color, 0.0, 0.9999); // Clamp values 0.0 <= color < 1.0
    color *= 256;                           // Translate to PPM color
    image << color;
}

auto getColor(const Ray& ray, const World& world, int depth) {
    if (depth == 0)
        return vec3{};

    std::optional<Hit> hit;
    for (const auto& figure : world) {
        auto tmax = hit ? hit->t : std::numeric_limits<double>::max();
        if (auto temp = figure->intersects(ray, tmin, tmax); temp && temp->t < tmax)
            hit = std::move(temp);
    }

    if (!hit)
        return calculateColor(ray);

    if (auto scattered = hit->material->scatter(*hit, ray))
        return scattered->attenuation * getColor(scattered->ray, world, --depth);

    return vec3{};
}

int main(int, char**) {
    constexpr auto camera = Camera(aspect_ratio, 2.0, 1.0);

    auto image = Image(aspect_ratio, 400, "output.ppm");
    auto world = World();

    auto material_ground = std::make_shared<Lambertian>(vec3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Dielectric>(1.5);
    auto material_left   = std::make_shared<Dielectric>(1.5);
    auto material_right  = std::make_shared<Metal>(vec3(0.8, 0.6, 0.2), 1.0);

    world.push_back(std::make_unique<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.push_back(std::make_unique<Sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
    world.push_back(std::make_unique<Sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.push_back(std::make_unique<Sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));

    for (auto i = image.height - 1; i >= 0; i--) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (auto j = 0; j < image.width; j++) {
            auto color = vec3();
            for (auto s = 0; s < samples_per_pixel; s++) {
                auto u   = double(j + random<double>()) / (image.width - 1);
                auto v   = double(i + random<double>()) / (image.height - 1);
                auto ray = camera.generate(u, v);
                color += getColor(ray, world, depth);
            }
            writeColor(image, color);
        }
    }
    return 0;
}