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
constexpr auto tmin              = 0.001;
constexpr auto samples_per_pixel = 100;
constexpr auto depth             = 50;
constexpr auto scale             = 1.0f / samples_per_pixel;

auto getRandomUnitVector() {
    auto u = random<glm::vec3>(-1.0, 1.0);
    while (glm::length(u) > 1.0f)
        u = random<glm::vec3>(-1.0, 1.0);
    return u;
}

auto calculateColor(const Ray& ray) {
    auto direction = glm::normalize(ray.direction);
    auto t         = 0.5f * (direction.y + 1.f); // Normalize to be between 0 and 1
    return glm::mix(glm::vec3{1.0, 1.0, 1.0}, glm::vec3{0.5, 0.7, 1.0}, t);
}

void writeColor(Image& image, glm::vec3 color) {
    color *= scale;                           // Average it by dividing by number of samples
    color = glm::sqrt(color);                 // Apply gamma 2.0
    color = glm::clamp(color, 0.0f, 0.9999f); // Clamp values 0.0 <= color < 1.0
    color *= 256;                             // Translate to PPM color
    image << color;
}

auto getColor(const Ray& ray, const World& world, int depth) {
    if (depth == 0)
        return glm::vec3{};

    std::optional<Hit> hit;
    for (const auto& figure : world) {
        auto tmax = hit ? std::get<2>(*hit) : std::numeric_limits<float>::infinity();
        if (auto temp = figure->intersects(ray, tmin, tmax)) {
            if (auto t = std::get<2>(*temp); t < tmax)
                hit = temp;
        }
    }

    if (hit) {
        auto& point  = std::get<0>(*hit);
        auto& normal = std::get<1>(*hit);
        auto target  = point + normal + getRandomUnitVector();
        return 0.5f * getColor({point, glm::normalize(target - point)}, world, --depth);
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
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (auto j = 0; j < image.width; j++) {
            auto color = glm::vec3();

            for (auto s = 0; s < samples_per_pixel; s++) {
                auto u   = float(j + random<float>()) / (image.width - 1);
                auto v   = float(i + random<float>()) / (image.height - 1);
                auto ray = camera.generate(u, v);
                color += getColor(ray, world, depth);
            }

            writeColor(image, color);
        }
    }
    return 0;
}