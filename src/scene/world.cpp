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

bool World::shadow(const PointLight &light, const Tuple &position) const
{
    Tuple light_dir = light.get_position() - position;
    double distance = magnitude(light_dir);
    Tuple normalized_light_dir = normalize(light_dir);

    std::vector<Intersection> xs = intersects(Ray{position, normalized_light_dir});
    auto i = hit(xs);
    if (i)
	return (i.value().get_t() < distance);
    else
	return false;
}

Tuple World::shade(const Computation &comp) const
{
    Tuple ret{color(0, 0, 0)};
    for (int i = 0; i < lights.size(); i++)
    {
	bool shadowed = shadow(lights.at(i), comp.get_over_point());
	ret += lighting(comp.get_object().get_material(), lights.at(i), comp.get_point(), comp.get_eye(), comp.get_normal(), shadowed);
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