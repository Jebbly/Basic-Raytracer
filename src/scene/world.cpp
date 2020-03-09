#include "scene/world.h"

World::World(const Tuple &ambient) :
    m_ambient{ambient}
{}

// accessor methods
void World::add_object(Primitive &object)
{
    m_objects.push_back(&object);
}

void World::add_light(Light &light)
{
    m_lights.push_back(&light);
}

// raytrace functions
std::vector<Intersection> World::intersects(const Ray &ray) const
{
    std::vector<Intersection> ret;
    for (int i = 0; i < m_objects.size(); i++)
    {
	std::vector<Intersection> object_intersects = intersect(m_objects.at(i), ray);
	ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

bool World::shadow(const Light *light, const Tuple &position) const
{
    Tuple light_dir = light->get_direction(position);
    double distance = magnitude(light_dir);
    Tuple normalized_light_dir = normalize(light_dir);

    std::vector<Intersection> xs = intersects(Ray{position, normalized_light_dir});
    auto i = hit(xs);
    if (i)
	return (i.value().get_t() < distance);
    else
	return false;
}

// raytrace functions
Tuple World::shade(const Computation &comp) const
{
    Tuple ret{color(0, 0, 0)};
    for (int i = 0; i < m_lights.size(); i++)
    {
	bool shadowed = shadow(m_lights.at(i), comp.get_over_point());
	if (!shadowed)
	    ret += m_lights.at(i)->lighting(comp);
    }
    ret += hadamard_product(m_ambient, comp.get_object()->get_material().get_color()) * comp.get_object()->get_material().get_ambient();
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