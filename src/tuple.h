#pragma once

#include <iostream>

struct tuple
{
    explicit tuple(const float _x = 0, const float _y = 0, const float _z = 0, const float _w = 0);

    union {
        float x = 0.0, r;
    };
    union {
        float y = 0.0, g;
    };
    union {
        float z = 0.0, b;
    };
    union {
        float w = 0.0, a;
    };

    static tuple zero();
};

tuple point(const float x = 0, const float y = 0, const float z = 0);
tuple vector(const float x = 0, const float y = 0, const float z = 0);

struct color : tuple
{
    color(const float _r, const float _g, const float _b);
    color(const tuple&);
    color() = default;

    static const color& black();
    static const color& white();
    static const color& red();
    static const color& green();
    static const color& blue();
    static const color& yellow();
};

color operator*(const color&, const color&);

bool operator==(const tuple&, const tuple&);
bool operator!=(const tuple&, const tuple&);
bool is_point(const tuple&);
bool is_vector(const tuple&);

float length(const tuple&);
float dot(const tuple&, const tuple&);

tuple operator+(const tuple&, const tuple&);
tuple& operator+=(tuple&, const tuple&);
tuple operator-(const tuple&, const tuple&);
tuple operator*(const tuple&, const float);
tuple operator*(float, const tuple&);
tuple operator/(const tuple&, const float);
tuple normalize(const tuple&);
tuple cross(const tuple&, const tuple&);
tuple operator-(const tuple&);

std::ostream& operator<<(std::ostream& os, const tuple&);