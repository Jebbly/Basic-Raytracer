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