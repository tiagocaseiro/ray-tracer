#include <gtest/gtest.h>

#include "ray.h"
#include "world.h"

TEST(world, Intersections)
{

    point_light light = point_light(make_point(-10, 10, -10));

    material m1 = material{};
    m1.color    = color(0.8, 1.0, 0.6);
    m1.diffuse  = 0.7;
    m1.specular = 0.2;
    sphere s1   = sphere();

    material m2 = material{};
    sphere s2   = sphere(m2, scale(0.5));

    world w = world(light, {s1, s2});

    ray r = ray{make_point(0, 0, -5), make_vector(0, 0, 1)};

    std::vector<hit> h = hits(r, w);

    EXPECT_EQ(h.size(), 4);
    EXPECT_EQ(h[0].inter.t, 4.f);
    EXPECT_EQ(h[1].inter.t, 4.5f);
    EXPECT_EQ(h[2].inter.t, 5.5f);
    EXPECT_EQ(h[3].inter.t, 6.f);
}

TEST(world, OutsideIntersection)
{
    ray r    = ray{make_point(0, 0, -5), make_vector(0, 0, 1)};
    sphere s = sphere{};
    hit h    = hit{intersection{4, &s}, r};

    EXPECT_FALSE(h.inside);
}

TEST(world, InsideIntersection)
{
    ray r    = ray{make_point(), make_vector(0, 0, 1)};
    sphere s = sphere{};
    hit h    = hit{intersection{1, &s}, r};

    EXPECT_EQ(h.point, make_point(0, 0, 1));
    EXPECT_EQ(h.eye_direction, make_vector(0, 0, -1));
    EXPECT_EQ(h.norm, make_vector(0, 0, -1));
    EXPECT_TRUE(h.inside);
}
