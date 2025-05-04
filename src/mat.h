#pragma once

// Disable Spectre related warning
#pragma warning(disable : 5045)

#include <algorithm>
#include <array>
#include <cmath>
#include <span>

#include "common.h"
#include "tuple.h"

namespace rt
{
    struct ray;

    template <size_t n>
    struct mat
    {
        explicit mat(const std::array<float, n * n>& _data = {}) : m_data(_data)
        {
        }

        [[nodiscard]] float& at(const size_t x, const size_t y)
        {
            return m_data[x * n + y];
        }

        [[nodiscard]] float at(const size_t x, const size_t y) const
        {
            return m_data[x * n + y];
        }

        static const mat<n>& identity()
        {
            static const mat<n> id = std::invoke([] {
                mat<n> m;
                for(size_t i = 0; i < n; i++)
                {
                    m.m_data[i * n + i] = 1;
                }
                return m;
            });
            return id;
        }

    private:
        std::array<float, n * n> m_data = {};
    };

    template <size_t n>
    bool operator==(const mat<n>& a, const mat<n>& b)
    {
        return (a != b) == false;
    }

    template <size_t n>
    bool operator!=(const mat<n>& a, const mat<n>& b)
    {
        for(int i = 0; i != n; i++)
        {
            for(int j = 0; j != n; j++)
            {
                if(equals(a.at(i, j), b.at(i, j)) == false)
                {
                    return true;
                }
            }
        }
        return false;
    }

    template <size_t n>
    mat<n> operator*(const mat<n>& a, const mat<n>& b)
    {
        mat<n> new_mat;

        for(size_t i = 0; i != n; i++)
        {
            for(size_t j = 0; j != n; j++)
            {
                for(size_t k = 0; k != n; k++)
                {
                    new_mat.at(i, j) += (a.at(i, k) * b.at(k, j));
                }
            }
        }

        return new_mat;
    }

    template <size_t n>
    mat<n> transpose(const mat<n>& m)
    {
        mat<n> new_m;
        for(size_t i = 0; i != n; i++)
        {
            for(size_t j = 0; j != n; j++)
            {
                new_m.at(i, j) = m.at(j, i);
            }
        }
        return new_m;
    }

    template <size_t n>
    float determinant(const mat<n>& m)
    {
        float determinant = 0.f;
        if constexpr(n == 2)
        {
            determinant = m.at(0, 0) * m.at(1, 1) - m.at(0, 1) * m.at(1, 0);
        }
        else
        {
            for(size_t j = 0; j != n; j++)
            {
                determinant += (m.at(0, j) * cofactor(m, 0, j));
            }
        }

        return determinant;
    }

    template <size_t n>
    mat<n - 1> submatrix(const mat<n>& m, const size_t x, const size_t y)
    {
        mat<n - 1> sub;

        size_t m_i = 0;
        for(size_t sub_i = 0; sub_i != n - 1; sub_i++)
        {
            if(m_i == x)
            {
                m_i++;
            }

            size_t m_j = 0;
            for(size_t sub_j = 0; sub_j != n - 1; sub_j++)
            {
                if(m_j == y)
                {
                    m_j++;
                }

                sub.at(sub_i, sub_j) = m.at(m_i, m_j);
                m_j++;
            }
            m_i++;
        }

        return sub;
    }

    float minor(const auto& m, const size_t x, const size_t y)
    {
        return determinant(submatrix(m, x, y));
    }

    float cofactor(const auto& m, const size_t x, const size_t y)
    {
        auto cofactor = minor(m, x, y);

        if((x + y) % 2 != 0)
        {
            cofactor *= -1;
        }

        return cofactor;
    }

    bool invertible(const auto& m)
    {
        return determinant(m) != 0;
    }

    template <size_t n>
    auto inverse(const mat<n>& m)
    {
        float d = determinant(m);
        if(d == 0)
        {
            throw std::domain_error("Attempted to invert a non-invertible matrix");
        }

        mat<n> m_inverse;
        for(size_t i = 0; i != n; i++)
        {
            for(size_t j = 0; j != n; j++)
            {
                m_inverse.at(j, i) = cofactor(m, i, j) / d;
            }
        }

        return m_inverse;
    }

    using mat4 = mat<4>;
    using mat3 = mat<3>;
    using mat2 = mat<2>;

    [[nodiscard]] tuple operator*(const mat4& m, const tuple& t);
    [[nodiscard]] ray operator*(const mat4& m, const ray& r);
    [[nodiscard]] mat4 translate(const float x, const float y, const float z);
    [[nodiscard]] mat4 scale(const float x, const float y, const float z);
    [[nodiscard]] mat4 scale(const float s);
    [[nodiscard]] mat4 rotate_x(const float angle_radians);
    [[nodiscard]] mat4 rotate_y(const float angle_radians);
    [[nodiscard]] mat4 rotate_z(const float angle_radians);
    [[nodiscard]] mat4 shear_x(const float y, const float z);
    [[nodiscard]] mat4 shear_y(const float x, const float z);
    [[nodiscard]] mat4 shear_z(const float x, const float y);
} // namespace rt

template <size_t n>
std::ostream& operator<<(std::ostream& os, const rt::mat<n>& mat)
{
    for(size_t i = 0; i != n; i++)
    {
        for(size_t j = 0; j != n; j++)
        {
            os << mat.at(i, j) << " ";
        }

        os << std::endl;
    }

    return os;
}