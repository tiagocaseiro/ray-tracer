#include <gtest/gtest.h>

#include <cmath>
#include <limits>

#include "common.h"
#include "tuple.h"

TEST(color, Ctor)
{
    color c{-0.5f, 0.4f, 1.7f};

    EXPECT_NEAR(c.r, -0.5, EPSILON);
    EXPECT_NEAR(c.g, 0.4, EPSILON);
    EXPECT_NEAR(c.b, 1.7, EPSILON);
}

TEST(color, Addition)
{
    color c1{0.9f, 0.6f, 0.75f};
    color c2{0.7f, 0.1f, 0.25f};

    color c3 = c1 + c2;

    color expected = {1.6f, 0.7, 1.0f};

    EXPECT_EQ(c3, expected);
}

TEST(color, Subtraction)
{
    color c1{0.9f, 0.6f, 0.75f};
    color c2{0.7f, 0.1f, 0.25f};

    color c3 = c1 - c2;

    color expected = {0.2f, 0.5, 0.5f};

    EXPECT_EQ(c3, expected);
}

TEST(color, Multiplication)
{
    color c1{0.2f, 0.3f, 0.4f};

    color expected = {0.4f, 0.6f, 0.8f};

    EXPECT_EQ(c1 * 2, expected);
}

TEST(color, Product)
{
    color c1{1.0f, 0.2f, 0.4f};
    color c2{0.9f, 1.0f, 0.1f};

    color expected = {0.9f, 0.2f, 0.04f};

    EXPECT_EQ(c1 * c2, expected);
}