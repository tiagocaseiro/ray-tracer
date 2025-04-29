#include "lighting.h"

#include "figures.h"

tuple normal(const sphere& s, tuple point)
{
    // Transform point to object space
    point = inverse(s.transform) * point;

    tuple normal = point - s.centre;

    // Transform normal to world space
    normal   = transpose(inverse(s.transform)) * normal;
    normal.w = 0;
    normal   = normalize(normal);

    return normal;
}

tuple reflect(const tuple& in, const tuple& normal)
{
    return in - normal * 2 * dot(in, normal);
}
