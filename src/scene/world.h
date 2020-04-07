#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "core/intersection.h"
#include "core/computation.h"
#include "scene/light.h"
#include "primitives/primitive.h"

namespace scene
{

class World
{
private:
    // attributes
    math::Tuple3d m_ambient;
    std::vector<light::Light*> m_lights;
    std::vector<Primitive*> m_objects;

public:
    World(const math::Tuple3d &ambient = math::color<double>(1, 1, 1));

    // accessor methods
    std::vector<light::Light*>& get_lights() {return m_lights;}
    std::vector<Primitive*>& get_objects() {return m_objects;}

    void add_object(Primitive &object);
    void add_light(light::Light &light);

    // raytrace functions
    std::vector<Intersection> intersects(const Ray &ray) const;
    bool shadow(const light::Light *light, const math::Tuple4d &position) const;
    math::Tuple3d reflection(const Computation &comp, int recursion_depth) const;
    math::Tuple3d refraction(const Computation &comp, int recursion_depth) const;
    double schlick(const Computation &comp) const;
    math::Tuple3d shade(const Computation &comp, int recursion_depth) const;
    math::Tuple3d final_color(const Ray &ray, int recursion_depth) const;
};

} // namespace scene

#endif