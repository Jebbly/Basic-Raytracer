#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "core/intersection.h"
#include "core/computation.h"
#include "scene/light.h"
#include "primitives/primitive.h"

class World
{
private:
    // attributes
    Tuple m_ambient;
    std::vector<Light*> m_lights;
    std::vector<Primitive*> m_objects;

public:
    World(const Tuple &ambient = color(1, 1, 1));

    // accessor methods
    std::vector<Light*>& get_lights() {return m_lights;}
    std::vector<Primitive*>& get_objects() {return m_objects;}

    void add_object(Primitive &object);
    void add_light(Light &light);

    // raytrace functions
    std::vector<Intersection> intersects(const Ray &ray) const;
    bool shadow(const Light *light, const Tuple &position) const;
    Tuple reflection(const Computation &comp, int recursion_depth) const;
    Tuple refraction(const Computation &comp, int recursion_depth) const;
    Tuple shade(const Computation &comp, int recursion_depth) const;
    Tuple final_color(const Ray &ray, int recursion_depth) const;
};

#endif