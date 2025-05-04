#include "mat.h"

#include "ray.h"
namespace rt
{
    tuple operator*(const mat4& m, const tuple& t)
    {
        return tuple{m.at(0, 0) * t.x + m.at(0, 1) * t.y + m.at(0, 2) * t.z + m.at(0, 3) * t.w,
                     m.at(1, 0) * t.x + m.at(1, 1) * t.y + m.at(1, 2) * t.z + m.at(1, 3) * t.w,
                     m.at(2, 0) * t.x + m.at(2, 1) * t.y + m.at(2, 2) * t.z + m.at(2, 3) * t.w,
                     m.at(3, 0) * t.x + m.at(3, 1) * t.y + m.at(3, 2) * t.z + m.at(3, 3) * t.w};
    }

    ray operator*(const mat4& m, const ray& r)
    {
        return {m * r.origin, m * r.direction};
    }

    mat4 translate(const float x, const float y, const float z)
    {
        auto mat     = mat4::identity();
        mat.at(0, 3) = x;
        mat.at(1, 3) = y;
        mat.at(2, 3) = z;
        return mat;
    }

    mat4 scale(const float x, const float y, const float z)
    {
        auto mat     = mat4::identity();
        mat.at(0, 0) = x;
        mat.at(1, 1) = y;
        mat.at(2, 2) = z;
        return mat;
    }

    mat4 scale(const float s)
    {
        return scale(s, s, s);
    }

    mat4 rotate_x(const float angle_radians)
    {
        auto mat = mat4::identity();

        mat.at(1, 1) = std::cos(angle_radians);
        mat.at(1, 2) = -std::sin(angle_radians);
        mat.at(2, 1) = std::sin(angle_radians);
        mat.at(2, 2) = std::cos(angle_radians);

        return mat;
    }

    mat4 rotate_y(const float angle_radians)
    {
        auto mat = mat4::identity();

        mat.at(0, 0) = std::cos(angle_radians);
        mat.at(0, 2) = std::sin(angle_radians);
        mat.at(2, 0) = -std::sin(angle_radians);
        mat.at(2, 2) = std::cos(angle_radians);

        return mat;
    }

    mat4 rotate_z(const float angle_radians)
    {
        auto mat = mat4::identity();

        mat.at(0, 0) = std::cos(angle_radians);
        mat.at(0, 1) = -std::sin(angle_radians);
        mat.at(1, 0) = std::sin(angle_radians);
        mat.at(1, 1) = std::cos(angle_radians);

        return mat;
    }

    mat4 shear_x(const float y, const float z)
    {
        auto mat     = mat4::identity();
        mat.at(0, 1) = y;
        mat.at(0, 2) = z;
        return mat;
    }

    mat4 shear_y(const float x, const float z)
    {
        auto mat     = mat4::identity();
        mat.at(1, 0) = x;
        mat.at(1, 2) = z;
        return mat;
    }

    mat4 shear_z(const float x, const float y)
    {
        auto mat     = mat4::identity();
        mat.at(2, 0) = x;
        mat.at(2, 1) = y;
        return mat;
    }
} // namespace rt