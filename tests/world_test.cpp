#include <gtest/gtest.h>

#include "world.h"

TEST(world, Intersections)
{
    world w;

    point_light light = point_light(make_point(-10, 10, -10));

    material m1 = material{};
    m1.color    = color(0.8, 1.0, 0.6);
    m1.diffuse  = 0.7;
    sphere s1   = sphere();

    material m2 = material{};
    sphere s2   = sphere(m2, scale(0.5));
}