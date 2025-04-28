#include <gtest/gtest.h>

#include <numbers>

#include "figures.h"
#include "lighting.h"

static constexpr auto PI = std::numbers::pi_v<float>;

TEST(normal, CenteredUnitSphere)
{
    sphere s;

    tuple normal = normal_at(s, make_point(1, 0, 0));

    EXPECT_EQ(normal, make_vector(1, 0, 0));

    normal = normal_at(s, make_point(0, 1, 0));

    EXPECT_EQ(normal, make_vector(0, 1, 0));

    normal = normal_at(s, make_point(0, 0, 1));

    EXPECT_EQ(normal, make_vector(0, 0, 1));

    normal = normal_at(s, make_point(std::sqrt(3) / 3.f, std::sqrt(3) / 3.f, std::sqrt(3) / 3.f));

    EXPECT_EQ(normal, make_vector(std::sqrt(3) / 3.f, std::sqrt(3) / 3.f, std::sqrt(3) / 3.f));

    EXPECT_EQ(normalize(normal), normal);
}

TEST(normal, TransformedSphere)
{
    sphere s = sphere(translate(0, 1, 0));

    tuple normal = normal_at(s, make_point(0, 1.70711, -0.70711));

    EXPECT_EQ(normal, make_vector(0, 0.70711, -0.70711));

    s = sphere(scale(1, 0.5, 1) * rotate_z(PI / 5.f));

    normal = normal_at(s, make_point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));

    EXPECT_EQ(normal, make_vector(0, 0.97014, -0.24254));
}
