#include "scene/world.h"

// accessor methods
void World::add_object(Sphere object)
{
    objects.push_back(object);
}

void World::add_light(PointLight light)
{
    lights.push_back(light);
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