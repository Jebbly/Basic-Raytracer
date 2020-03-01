#include "scene/world.h"

World::World()
{
    lights.push_back(PointLight{color(1, 1, 1), point(-10, 10, -10)});
    objects.push_back(Sphere{identity().scale(0.5, 0.5, 0.5)});
    objects.push_back(Sphere{identity(), Material{color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2}});
}

// raytrace functions
std::vector<Intersection> World::intersects(const Ray &ray) const
{
    std::vector<Intersection> ret;
    for (int i = 0; i < objects.size(); i++)
    {
	std::vector<Intersection> object_intersects = intersections(ray, objects.at(i));
	ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

Tuple World::shade(const Computation &comp) const
{
    Tuple ret{color(0, 0, 0)};
    for (int i = 0; i < lights.size(); i++)
    {
	ret += lighting(comp.get_object().get_material(), lights.at(i), comp.get_point(), comp.get_eye(), comp.get_normal());
    }
    return ret;
}

Tuple World::final_color(const Ray &ray) const
{
    std::vector<Intersection> xs = intersects(ray);
    auto intersect = hit(xs);
    if (intersect)
	return shade(Computation{ray, intersect.value()});
    else
	return color(0, 0, 0);
}