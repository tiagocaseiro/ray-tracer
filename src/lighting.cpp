#include "lighting.h"

#include "figures.h"
#include "material.h"
#include "ray.h"
#include "world.h"

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

    const color specular = light.intensity * material.specular * factor;

    std::cout << "effective_color: " << effective_color << std::endl;
    std::cout << "ambient: " << ambient << std::endl;
    std::cout << "diffuse: " << diffuse << std::endl;
    std::cout << "specular: " << specular << std::endl;
    return ambient + diffuse + specular;
}

color shade(const world& world, const hit& h)
{
    color result = color::black();

    for(const point_light& light : world.point_lights)
    {
        result += shade(h.figure->material, light, h.eye_direction, h.point, h.norm);
    }

    return result;
}

tuple normal(const figure& f, tuple point)
{
    if(const sphere* s = dynamic_cast<const sphere*>(&f))
    {
        return normal(*s, point);
    }

    return vector();
}

color shade(const world& w, const ray& r)
{
    std::cout << r << std::endl;
    std::vector<hit> h = hits(r, w);
    if(h.empty())
    {
        return color::black();
    }

    for(const auto& hit : h)
    {
        if(hit.t > 0)
        {
            return shade(w, hit);
        }
    }
    return color::black();
}
