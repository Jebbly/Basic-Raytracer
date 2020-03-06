#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "core/intersection.h"
#include "core/computation.h"
#include "scene/lighting.h"
#include "primitives/sphere.h"

class World
{
private:
    // attributes
    std::vector<PointLight> lights;
    std::vector<Sphere> objects;

public:
    // accessor methods
    std::vector<PointLight>& get_lights() {return lights;}
    std::vector<Sphere>& get_objects() {return objects;}

    void add_object(Sphere object);
    void add_light(PointLight light);

    // raytrace functions
    std::vector<Intersection> intersects(const Ray &ray) const;
    bool shadow(const PointLight &light, const Tuple &position) const;
    Tuple shade(const Computation &comp) const;
    Tuple final_color(const Ray &ray) const;
};

#endif