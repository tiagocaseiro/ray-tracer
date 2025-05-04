#include <gtest/gtest.h>

#include <numbers>

#include "figures.h"
#include "lighting.h"

static constexpr auto PI = std::numbers::pi_v<float>;

TEST(lighting, CenteredUnitSphere)
{
    sphere s;

    tuple n = normal(&s, make_point(1, 0, 0));

    EXPECT_EQ(n, make_vector(1, 0, 0));

    n = normal(&s, make_point(0, 1, 0));

    EXPECT_EQ(n, make_vector(0, 1, 0));

    n = normal(&s, make_point(0, 0, 1));

    EXPECT_EQ(n, make_vector(0, 0, 1));

    n = normal(&s, make_point(std::sqrt(3) / 3.f, std::sqrt(3) / 3.f, std::sqrt(3) / 3.f));

    EXPECT_EQ(n, make_vector(std::sqrt(3) / 3.f, std::sqrt(3) / 3.f, std::sqrt(3) / 3.f));

    EXPECT_EQ(normalize(n), n);
}

TEST(lighting, TransformedSphere)
{
    sphere s = sphere(translate(0, 1, 0));

    tuple n = normal(&s, make_point(0, 1.70711, -0.70711));

    EXPECT_EQ(n, make_vector(0, 0.70711, -0.70711));

    s = sphere(scale(1, 0.5, 1) * rotate_z(PI / 5.f));

    n = normal(&s, make_point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));

    EXPECT_EQ(n, make_vector(0, 0.97014, -0.24254));
}

TEST(lighting, Reflection)
{
    auto v = make_vector(1, -1, 0);
    auto n = make_vector(0, 1, 0);

    auto r = reflect(v, n);

    EXPECT_EQ(r, make_vector(1, 1, 0));

    v = make_vector(0, -1, 0);
    n = make_vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);

    r = reflect(v, n);

    EXPECT_EQ(r, make_vector(1, 0, 0));
}

TEST(lighting, Eye0DegreesLight0DegreesShade)
{
    const material material;
    const tuple point = make_point();

    tuple eye         = make_vector(0, 0, -1);
    tuple normal      = make_vector(0, 0, -1);
    point_light light = point_light{make_point(0, 0, -10)};

    color result = shade(material, light, eye, point, normal);

    EXPECT_EQ(result, color(1.9, 1.9, 1.9));
}

TEST(lighting, Eye45DegreesLight0DegreesShade)
{
    const material material;
    const tuple point = make_point();

    tuple eye         = make_vector(0, std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f);
    tuple normal      = make_vector(0, 0, -1);
    point_light light = point_light{make_point(0, 0, -10)};

    color result = shade(material, light, eye, point, normal);

    EXPECT_EQ(result, color(1.0, 1.0, 1.0));
}

TEST(lighting, Eye0DegreesLight45DegreesShade)
{
    const material material;
    const tuple point = make_point();

    tuple eye         = make_vector(0, 0, -1);
    tuple normal      = make_vector(0, 0, -1);
    point_light light = point_light{make_point(0, 10, -10)};

    color result = shade(material, light, eye, point, normal);

    EXPECT_EQ(result, color(std::sqrt(2) / 2 * 0.9 + 0.1, std::sqrt(2) / 2 * 0.9 + 0.1, std::sqrt(2) / 2 * 0.9 + 0.1));
}

TEST(lighting, EyeMinus45DegreesLight45DegreesShade)
{
    const material material;
    const tuple point = make_point();

    tuple eye         = make_vector(0, -std::sqrt(2.0f) / 2.0f, -std::sqrt(2.0f) / 2.0f);
    tuple normal      = make_vector(0, 0, -1);
    point_light light = point_light{make_point(0, 10, -10)};

    color result = shade(material, light, eye, point, normal);

    EXPECT_EQ(result, color(1.63639f, 1.63639f, 1.63639f));
}

TEST(lighting, Eye0DegreesLight180DegreesShade)
{
    const material material;
    const tuple point = make_point();

    tuple eye         = make_vector(0, 0, -1);
    tuple normal      = make_vector(0, 0, -1);
    point_light light = point_light{make_point(0, 0, 10)};

    color result = shade(material, light, eye, point, normal);

    EXPECT_EQ(result, color(0.1f, 0.1f, 0.1f));
}