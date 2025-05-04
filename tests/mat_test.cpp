#include <gtest/gtest.h>

#include <fstream>
#include <numbers>
#include <sstream>


#include "mat.h"
#include "tuple.h"

using namespace std::numbers;
using namespace rt;

TEST(mat, At)
{
    mat4 mat_a({1.f, 2.f, 3.f, 4.f, 5.5f, 6.5f, 7.5f, 8.5f, 9.f, 10.f, 11.f, 12.f, 13.5f, 14.5f, 15.5f, 16.5f});

    EXPECT_EQ(mat_a.at(0, 0), 1);
    EXPECT_EQ(mat_a.at(0, 3), 4);
    EXPECT_EQ(mat_a.at(1, 0), 5.5);
    EXPECT_EQ(mat_a.at(1, 2), 7.5);
    EXPECT_EQ(mat_a.at(2, 2), 11);
    EXPECT_EQ(mat_a.at(3, 0), 13.5);
    EXPECT_EQ(mat_a.at(3, 2), 15.5);

    mat2 mat_b({-3.f, 5.f, 1.f, -2.f});

    EXPECT_EQ(mat_b.at(0, 0), -3);
    EXPECT_EQ(mat_b.at(0, 1), 5);
    EXPECT_EQ(mat_b.at(1, 0), 1);
    EXPECT_EQ(mat_b.at(1, 1), -2);

    mat3 mat_c({
        -3.f,
        5.f,
        0.f,
        1.f,
        -2.f,
        -7.f,
        0.f,
        1.f,
        1.f,
    });

    EXPECT_EQ(mat_c.at(0, 0), -3);
    EXPECT_EQ(mat_c.at(1, 1), -2);
    EXPECT_EQ(mat_c.at(2, 2), 1);
}

TEST(mat, Equals)
{
    mat4 mat_a({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f});

    mat4 mat_b({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f});

    EXPECT_EQ(mat_a, mat_b);
    EXPECT_FALSE(mat_a != mat_b);
}

TEST(mat, NotEquals)
{
    mat4 mat_a({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f});

    mat4 mat_b({2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f});

    EXPECT_NE(mat_a, mat_b);
    EXPECT_TRUE(mat_a != mat_b);
}

TEST(mat, Multiplication)
{
    mat4 mat_a({1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 8.f, 7.f, 6.f, 5.f, 4.f, 3.f, 2.f});

    mat4 mat_b({-2.f, 1.f, 2.f, 3.f, 3.f, 2.f, 1.f, -1.f, 4.f, 3.f, 6.f, 5.f, 1.f, 2.f, 7.f, 8.f});

    mat4 result({20.f, 22.f, 50.f, 48.f, 44.f, 54.f, 114.f, 108.f, 40.f, 58.f, 110.f, 102.f, 16.f, 26.f, 46.f, 42.f});

    EXPECT_EQ(mat_a * mat_b, result);
}

TEST(mat, MultiplicationTuple)
{
    mat4 m({1.f, 2.f, 3.f, 4.f, 2.f, 4.f, 4.f, 2.f, 8.f, 6.f, 4.f, 1.f, 0.f, 0.f, 0.f, 1.f});

    tuple t{1, 2, 3, 1};

    tuple expected{18, 24, 33, 1};

    EXPECT_EQ(m * t, expected);
}

TEST(mat, MultiplicationIdentity)
{
    mat4 m({1.f, 2.f, 3.f, 4.f, 5.5f, 6.5f, 7.5f, 8.5f, 9.f, 10.f, 11.f, 12.f, 13.5f, 14.5f, 15.5f, 16.5f});

    EXPECT_EQ(m * mat4::identity(), m);
}

TEST(mat, MultiplicationIdentityTuple)
{
    tuple t{1, 2, 3, 4};

    EXPECT_EQ(mat4::identity() * t, t);
}

TEST(mat, Transpose)
{
    mat4 m({0.f, 9.f, 3.f, 0.f, 9.f, 8.f, 0.f, 8.f, 1.f, 8.f, 5.f, 3.f, 0.f, 0.f, 5.f, 8.f});

    mat4 expected({0.f, 9.f, 1.f, 0.f, 9.f, 8.f, 8.f, 0.f, 3.f, 0.f, 5.f, 5.f, 0.f, 8.f, 3.f, 8.f});

    EXPECT_EQ(transpose(m), expected);
}

TEST(mat, TransposeIdentity)
{
    EXPECT_EQ(transpose(mat4::identity()), mat4::identity());
}

TEST(mat, Submatrix1)
{
    mat3 m({1.f, 5.f, 9.f, -3.f, 2.f, 7.f, 0.f, 6.f, -3.f});

    mat2 expected({-3.f, 2.f, 0.f, 6.f});

    EXPECT_EQ(submatrix(m, 0, 2), expected);
}

TEST(mat, Submatrix2)
{
    mat4 m({-6.f, 1.f, 1.f, 6.f, -8.f, 5.f, 8.f, 6.f, -1.f, 0.f, 8.f, 2.f, -7.f, 1.f, -1.f, 1.f});

    mat3 expected({-6.f, 1.f, 6.f, -8.f, 8.f, 6.f, -7.f, -1.f, 1.f});

    EXPECT_EQ(submatrix(m, 2, 1), expected);
}

TEST(mat, Minor)
{
    mat3 m({3.f, 5.f, 0.f, 2.f, -1.f, -7.f, 6.f, -1.f, 5.f});

    EXPECT_EQ(determinant(submatrix(m, 1, 0)), 25);
    EXPECT_EQ(minor(m, 1, 0), 25);
}

TEST(mat, Determinant)
{
    mat3 m_a({1.f, 2.f, 6.f, -5.f, 8.f, -4.f, 2.f, 6.f, 4.f});

    EXPECT_EQ(cofactor(m_a, 0, 0), 56);
    EXPECT_EQ(cofactor(m_a, 0, 1), 12);
    EXPECT_EQ(cofactor(m_a, 0, 2), -46);
    EXPECT_EQ(determinant(m_a), -196);

    mat4 m_b({-2.f, -8.f, 3.f, 5.f, -3.f, 1.f, 7.f, 3.f, 1.f, 2.f, -9.f, 6.f, -6.f, 7.f, 7.f, -9.f});

    EXPECT_EQ(cofactor(m_b, 0, 0), 690);
    EXPECT_EQ(cofactor(m_b, 0, 1), 447);
    EXPECT_EQ(cofactor(m_b, 0, 2), 210);
    EXPECT_EQ(cofactor(m_b, 0, 3), 51);
    EXPECT_EQ(determinant(m_b), -4071);

    mat2 m_c({1.f, 5.f, -3.f, 2.f});

    EXPECT_EQ(determinant(m_c), 17.f);
}

TEST(mat, Invertible)
{
    mat4 m({6.f, 4.f, 4.f, 4.f, 5.f, 5.f, 7.f, 6.f, 4.f, -9.f, 3.f, -7.f, 9.f, 1.f, 7.f, -6.f});

    EXPECT_EQ(determinant(m), -2120);
    EXPECT_TRUE(invertible(m));
}

TEST(mat, NonInvertible)
{
    mat4 m({-4.f, 2.f, -2.f, -3.f, 9.f, 6.f, 2.f, 6.f, 4.f, -5.f, 1.f, -5.f, 0.f, 0.f, 0.f, 0.f});

    EXPECT_EQ(determinant(m), 0);
    EXPECT_FALSE(invertible(m));
    EXPECT_ANY_THROW(inverse(m));
}

TEST(mat, Inverse1)
{
    mat4 m({-5.f, 2.f, 6.f, -8.f, 1.f, -5.f, 1.f, 8.f, 7.f, 7.f, -6.f, -7.f, 1.f, -3.f, 7.f, 4.f});

    mat4 inverted = inverse(m);
    mat4 expected({0.21805f, 0.45113f, 0.24060f, -0.04511f, -0.80827f, -1.45677f, -0.44361f, 0.52068f, -0.07895f,
                   -0.22368f, -0.05263f, 0.19737f, -0.52256f, -0.81391f, -0.30075f, 0.30639f});
    EXPECT_EQ(determinant(m), 532);
    EXPECT_EQ(cofactor(m, 2, 3), -160);
    EXPECT_EQ(inverted.at(3, 2), -160.f / 532.f);
    EXPECT_EQ(cofactor(m, 3, 2), 105);
    EXPECT_EQ(inverted.at(2, 3), 105.f / 532.f);
    EXPECT_EQ(inverted, expected);
}

TEST(mat, Inverse2)
{
    mat4 m({8.f, -5.f, 9.f, 2.f, 7.f, 5.f, 6.f, 1.f, -6.f, 0.f, 9.f, 6.f, -3.f, 0.f, -9.f, -4.f});

    mat4 inverted = inverse(m);

    mat4 expected({-0.15385f, -0.15385f, -0.28205f, -0.53846f, -0.07692f, 0.12308f, 0.02564f, 0.03077f, 0.35897f,
                   0.35897f, 0.43590f, 0.92308f, -0.69231f, -0.69231f, -0.76923f, -1.92308f});

    EXPECT_EQ(inverted, expected);
}

TEST(mat, Inverse3)
{

    mat4 m({9.f, 3.f, 0.f, 9.f, -5.f, -2.f, -6.f, -3.f, -4.f, 9.f, 6.f, 4.f, -7.f, 6.f, 6.f, 2.f});

    mat4 inverted = inverse(m);

    mat4 expected({-0.04074f, -0.07778f, 0.14444f, -0.22222f, -0.07778f, 0.03333f, 0.36667f, -0.33333f, -0.02901f,
                   -0.14630f, -0.10926f, 0.12963f, 0.17778f, 0.06667f, -0.26667f, 0.33333f});

    EXPECT_EQ(inverted, expected);
}

TEST(mat, InverseIdentity)
{
    EXPECT_EQ(inverse(mat4::identity()), mat4::identity());
}

TEST(mat, InverseMultiplication1)
{

    mat4 m_a({3.f, -9.f, 7.f, 3.f, 3.f, -8.f, 2.f, -9.f, -4.f, 4.f, 4.f, 1.f, -6.f, 5.f, -1.f, 1.f});

    mat4 m_b({8.f, 2.f, 2.f, 2.f, 3.f, -1.f, 7.f, 0.f, 7.f, 0.f, 5.f, 4.f, 6.f, -2.f, 0.f, 5.f});

    mat4 m_c = m_a * m_b;

    mat4 inverted = m_c * inverse(m_b);

    EXPECT_EQ(inverted, m_a);
}

TEST(mat, InverseMultiplication2)
{

    mat4 m({3.f, -9.f, 7.f, 3.f, 3.f, -8.f, 2.f, -9.f, -4.f, 4.f, 4.f, 1.f, -6.f, 5.f, -1.f, 1.f});

    EXPECT_EQ(inverse(m) * m, mat4::identity());
}

TEST(mat, InverseTranspose)
{

    mat4 m({3.f, -9.f, 7.f, 3.f, 3.f, -8.f, 2.f, -9.f, -4.f, 4.f, 4.f, 1.f, -6.f, 5.f, -1.f, 1.f});

    EXPECT_EQ(inverse(transpose(m)), transpose(inverse(m)));
}

TEST(mat, InverseMultiplicationTuple)
{

    mat4 m({3.f, -9.f, 7.f, 3.f, 3.f, -8.f, 2.f, -9.f, -4.f, 4.f, 4.f, 1.f, -6.f, 5.f, -1.f, 1.f});

    tuple t(1, 2, 3, 4);

    tuple v = m * t;

    tuple inverted = inverse(m) * v;

    EXPECT_EQ(inverted, t);
}

TEST(mat, TranslationPoint)
{
    auto m = translate(5, -3, 2);
    auto p = make_point(-3, 4, 5);

    auto q = m * p;

    EXPECT_EQ(q, make_point(2, 1, 7));
}

TEST(mat, TranslationPointInverse)
{
    auto m = inverse(translate(5, -3, 2));
    auto p = make_point(-3, 4, 5);

    auto q = m * p;

    EXPECT_EQ(q, make_point(-8, 7, 3));
}

TEST(mat, TranslationVector)
{
    auto m = inverse(translate(5, -3, 2));
    auto p = make_vector(-3, 4, 5);

    auto q = m * p;

    EXPECT_EQ(q, p);
}

TEST(mat, ScalePoint)
{
    auto m = scale(2, 3, 4);
    auto p = make_point(-4, 6, 8);

    auto q = m * p;

    EXPECT_EQ(q, make_point(-8, 18, 32));
}

TEST(mat, ScaleVector)
{
    auto m = scale(2, 3, 4);
    auto p = make_vector(-4, 6, 8);

    auto q = m * p;

    EXPECT_EQ(q, make_vector(-8, 18, 32));
}

TEST(mat, ScaleVectorInverse)
{
    auto m = inverse(scale(2, 3, 4));
    auto p = make_vector(-4, 6, 8);

    auto q = m * p;

    EXPECT_EQ(q, make_vector(-2, 2, 2));
}

TEST(mat, ReflectPoint)
{
    auto m = scale(-1, 1, 1);
    auto p = make_point(2, 3, 4);

    auto q = m * p;

    EXPECT_EQ(q, make_point(-2, 3, 4));
}

TEST(mat, RotationX)
{
    auto p = make_point(0, 1, 0);

    auto half_quarter = rotate_x(pi / 4);
    auto full_quarter = rotate_x(pi / 2);

    EXPECT_EQ(half_quarter * p, make_point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
    EXPECT_EQ(full_quarter * p, make_point(0, 0, 1));
}

TEST(mat, RotationXInverse)
{
    auto p = make_point(0, 1, 0);

    auto half_quarter_inverse = inverse(rotate_x(pi / 4));

    EXPECT_EQ(half_quarter_inverse * p, make_point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
}

TEST(mat, RotationY)
{
    auto p = make_point(0, 0, 1);

    auto half_quarter = rotate_y(pi / 4);
    auto full_quarter = rotate_y(pi / 2);

    EXPECT_EQ(half_quarter * p, make_point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
    EXPECT_EQ(full_quarter * p, make_point(1, 0, 0));
}

TEST(mat, RotationZ)
{
    auto p = make_point(0, 1, 0);

    auto half_quarter = rotate_z(pi / 4);
    auto full_quarter = rotate_z(pi / 2);

    EXPECT_EQ(half_quarter * p, make_point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
    EXPECT_EQ(full_quarter * p, make_point(-1, 0, 0));
}

TEST(mat, ShearingXToY)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_x(1, 0);

    EXPECT_EQ(mat * p, make_point(5, 3, 4));
}

TEST(mat, ShearingXToZ)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_x(0, 1);

    EXPECT_EQ(mat * p, make_point(6, 3, 4));
}

TEST(mat, ShearingYToX)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_y(1, 0);

    EXPECT_EQ(mat * p, make_point(2, 5, 4));
}

TEST(mat, ShearingYToZ)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_y(0, 1);

    EXPECT_EQ(mat * p, make_point(2, 7, 4));
}

TEST(mat, ShearingZToX)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_z(1, 0);

    EXPECT_EQ(mat * p, make_point(2, 3, 6));
}

TEST(mat, ShearingZToY)
{
    auto p = make_point(2, 3, 4);

    auto mat = shear_z(0, 1);

    EXPECT_EQ(mat * p, make_point(2, 3, 7));
}

TEST(mat, IndividualTransform)
{
    auto p = make_point(1, 0, 1);

    auto mat_a = rotate_x(pi / 2);
    auto mat_b = scale(5, 5, 5);
    auto mat_c = translate(10, 5, 7);

    p = mat_a * p;
    EXPECT_EQ(p, make_point(1, -1, 0));

    p = mat_b * p;
    EXPECT_EQ(p, make_point(5, -5, 0));

    p = mat_c * p;
    EXPECT_EQ(p, make_point(15, 0, 7));
}

TEST(mat, ChainedTransform)
{
    auto p = make_point(1, 0, 1);

    auto mat_a = rotate_x(pi / 2);
    auto mat_b = scale(5, 5, 5);
    auto mat_c = translate(10, 5, 7);

    auto mat = mat_c * mat_b * mat_a;

    p = mat * p;
    EXPECT_EQ(p, make_point(15, 0, 7));
}