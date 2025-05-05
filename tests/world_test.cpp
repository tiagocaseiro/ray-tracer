#include <gtest/gtest.h>

#include "ray.h"
#include "world.h"

world default_world()
{
    point_light light = point_light(point(-10, 10, -10));

    material m1 = material{};
    m1.color    = color(0.8, 1.0, 0.6);
    m1.diffuse  = 0.7;
    m1.specular = 0.2;
    sphere s1   = sphere(m1);

    material m2 = material{};
    sphere s2   = sphere(m2, scale(0.5));

    return world({light}, {s1, s2});
}
TEST(world, Intersections)
{
    world w = default_world();
    ray r   = ray{point(0, 0, -5), vector(0, 0, 1)};

    std::vector<hit> h = hits(r, w);

    EXPECT_EQ(h.size(), 4);
    EXPECT_EQ(h[0].t, 4.f);
    EXPECT_EQ(h[1].t, 4.5f);
    EXPECT_EQ(h[2].t, 5.5f);
    EXPECT_EQ(h[3].t, 6.f);
}

TEST(world, OutsideIntersection)
{
    ray r    = ray{point(0, 0, -5), vector(0, 0, 1)};
    sphere s = sphere{};
    hit h    = hit{intersection{4, &s}, r};

    EXPECT_FALSE(h.inside);
}

TEST(world, InsideIntersection)
{
    ray r    = ray{point(), vector(0, 0, 1)};
    sphere s = sphere{};
    hit h    = hit{intersection{1, &s}, r};

    EXPECT_EQ(h.point, point(0, 0, 1));
    EXPECT_EQ(h.eye_direction, vector(0, 0, -1));
    EXPECT_EQ(h.norm, vector(0, 0, -1));
    EXPECT_TRUE(h.inside);
}

TEST(world, ShadeMiss)
{
    world w = default_world();
    ray r   = ray(point(0, 0, -5), vector(0, 1, 0));

    EXPECT_EQ(color::black(), shade(w, r));
}

TEST(world, ShadeHit)
{
    world w = default_world();
    ray r   = ray(point(0, 0, -5), vector(0, 0, 1));

    EXPECT_EQ(color(0.38066, 0.47583, 0.2855), shade(w, r));
}

TEST(world, ShadeHitOnInnerInsideOuter)
{
    world w = default_world();

    w.spheres[0].material.ambient = 1;
    w.spheres[1].material.ambient = 1;

    ray r = ray(point(0, 0, 0.75), vector(0, 0, -1));

    EXPECT_EQ(w.spheres[1].material.color, shade(w, r));
}
