#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "core/intersection.h"
#include "scene/lighting.h"
#include "primitives/sphere.h"

class World
{
private:
    // attributes
    std::vector<PointLight> lights;
    std::vector<Sphere> objects;

public:
    World();

    // accessor methods
    std::vector<PointLight>& get_lights() {return lights;}
    std::vector<Sphere>& get_objects() {return objects;}

    // raytrace functions
    std::vector<Intersection> intersects(const Ray &ray) const;
};

#endif