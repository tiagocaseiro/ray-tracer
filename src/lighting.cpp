#include "lighting.h"

#include "figures.h"
#include "material.h"

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

color shade(const material& material, const point_light& light, const tuple& eye, const tuple& point,
            const tuple& normal)
{
    const color effective_color = material.color * light.intensity;

    const color ambient = effective_color * material.ambient;

    const tuple light_to_point = normalize(light.position - point);

    const float light_normal_dot = std::max(dot(light_to_point, normal), 0.0f);

    const color diffuse = light_normal_dot * effective_color * material.diffuse;

    const tuple reflected_light_v = reflect(-light_to_point, normal);

    const float reflected_eye_dot = std::max(dot(reflected_light_v, eye), 0.0f);

    const float factor = std::pow(reflected_eye_dot, material.shininess);

    const color reflected = light.intensity * material.specular * factor;

    return ambient + diffuse + reflected;
}

tuple normal(const figure& f, tuple point)
{
    if(const sphere* s = dynamic_cast<const sphere*>(&f))
    {
        return normal(*s, point);
    }

    return make_vector();
}
