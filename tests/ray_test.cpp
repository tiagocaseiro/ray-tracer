#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

#include "mat.h"
#include "ray.h"

TEST(ray, Ctor)
{
    tuple origin    = make_point(1, 2, 3);
    tuple direction = make_vector(4, 5, 6);
    ray r           = ray{origin, direction};

    EXPECT_EQ(r.origin, origin);
    EXPECT_EQ(r.direction, direction);
}

TEST(ray, Position)
{
    tuple origin    = make_point(2, 3, 4);
    tuple direction = make_vector(1, 0, 0);
    ray r           = ray{origin, direction};

    EXPECT_EQ(position(r, 0.f), origin);
    EXPECT_EQ(position(r, 1.f), make_point(3, 3, 4));
    EXPECT_EQ(position(r, -1.f), make_point(1, 3, 4));
    EXPECT_EQ(position(r, 2.5f), make_point(4.5, 3, 4));
}

TEST(ray, SphereIntersection)
{
    sphere s;
    ray r = ray{make_point(0, 0, -5), make_vector(0, 0, 1)};

    std::vector<intersection> intersections = intersects(r, s);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 4.0f);
    EXPECT_EQ(intersections[1].t, 6.0f);
    EXPECT_EQ(intersections[0].figure, &s);
    EXPECT_EQ(intersections[1].figure, &s);

    r = ray{make_point(0, 1, -5), make_vector(0, 0, 1)};

    intersections = intersects(r, s);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, 5.0f);
    EXPECT_EQ(intersections[1].t, 5.0f);
    EXPECT_EQ(intersections[0].figure, &s);
    EXPECT_EQ(intersections[1].figure, &s);

    r = ray{make_point(0, 2, -5), make_vector(0, 0, 1)};

    intersections = intersects(r, s);

    EXPECT_TRUE(intersections.empty());

    r = ray{make_point(0, 0, 0), make_vector(0, 0, 1)};

    intersections = intersects(r, s);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, -1.0f);
    EXPECT_EQ(intersections[1].t, 1.0f);
    EXPECT_EQ(intersections[0].figure, &s);
    EXPECT_EQ(intersections[1].figure, &s);

    r = ray{make_point(0, 0, 5), make_vector(0, 0, 1)};

    intersections = intersects(r, s);

    EXPECT_EQ(intersections.size(), 2);
    EXPECT_EQ(intersections[0].t, -6.0f);
    EXPECT_EQ(intersections[1].t, -4.0f);
    EXPECT_EQ(intersections[0].figure, &s);
    EXPECT_EQ(intersections[1].figure, &s);
}

TEST(ray, Intersection)
{
    sphere s;

    intersection inter = intersection{3.5, &s};

    EXPECT_EQ(inter.t, 3.5);
    EXPECT_EQ(inter.figure, &s);
}

TEST(ray, Hit)
{
    sphere s;

    intersection inter1 = {1, &s};
    intersection inter2 = {2, &s};

    std::optional<intersection> inter = hit({inter2, inter1});

    EXPECT_TRUE(inter);
    EXPECT_EQ(inter->t, 1);

    inter1 = {-1, &s};
    inter2 = {1, &s};

    inter = hit({inter2, inter1});

    EXPECT_TRUE(inter);
    EXPECT_EQ(inter->t, 1);

    inter1 = {-2, &s};
    inter2 = {-1, &s};

    inter = hit({inter2, inter1});

    inter1 = {5, &s};
    inter2 = {7, &s};

    intersection inter3 = {3, &s};
    intersection inter4 = {2, &s};

    inter = hit({inter1, inter2, inter3, inter4});

    EXPECT_TRUE(inter);
    EXPECT_EQ(inter->t, 2);
}

TEST(ray, Transformation)
{
    ray r  = ray{make_point(1, 2, 3), make_vector(0, 1, 0)};
    mat4 m = translate(3, 4, 5);

    auto rt = m * r;

    EXPECT_EQ(rt.origin, make_point(4, 6, 8));
    EXPECT_EQ(rt.direction, make_vector(0, 1, 0));

    r = ray{make_point(1, 2, 3), make_vector(0, 1, 0)};
    m = scale(2, 3, 4);

    rt = m * r;

    EXPECT_EQ(rt.origin, make_point(2, 6, 12));
    EXPECT_EQ(rt.direction, make_vector(0, 3, 0));
}

TEST(ray, SphereTransformation)
{
    sphere s = sphere{scale(2)};
    ray r    = ray{make_point(0, 0, -5), make_vector(0, 0, 1)};

    std::vector<intersection> inters = intersects(r, s);

    EXPECT_EQ(inters.size(), 2);
    // EXPECT_EQ(inters[0].t, 3);
    // EXPECT_EQ(inters[1].t, 7);

    // s = sphere{translate(5, 0, 0)};

    // inters = intersects(r, s);

    // EXPECT_TRUE(inters.empty());
}