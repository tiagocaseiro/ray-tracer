#include "camera.h"
#include "canvas.h"
#include "ray.h"

int main()
{
    canvas c   = canvas(640, 360);
    camera cam = camera(c, 45.0);

    c.shade_pixels([&cam](const glm::vec2& pixel) {
        return color::BLACK;
    });

    c.save_to_file("result.ppm");
    return 0;
}