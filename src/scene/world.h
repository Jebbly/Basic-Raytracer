#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "core/intersection.h"
#include "core/computation.h"
#include "scene/lights/light.h"
#include "geometry/primitives/primitive.h"

namespace scene
{

class World
{
private:
    // attributes
    math::Tuple3d m_ambient;
    std::vector<light::Light*> m_lights;
    std::vector<geometry::primitive::Primitive*> m_objects;

public:
    World(const math::Tuple3d &ambient = math::color<double>(1, 1, 1));

    // accessor methods
    std::vector<light::Light*>& get_lights() {return m_lights;}
    std::vector<geometry::primitive::Primitive*>& get_objects() {return m_objects;}

    void add_object(geometry::primitive::Primitive &object);
    void add_light(light::Light &light);

    // raytrace functions
    std::vector<core::Intersection> intersects(const core::Ray &ray) const;
    bool shadow(const light::Light *light, const math::Tuple4d &position) const;
    math::Tuple3d reflection(const core::Computation &comp, int recursion_depth) const;
    math::Tuple3d refraction(const core::Computation &comp, int recursion_depth) const;
    double schlick(const core::Computation &comp) const;
    math::Tuple3d shade(const core::Computation &comp, int recursion_depth) const;
    math::Tuple3d final_color(const core::Ray &ray, int recursion_depth) const;
};

} // namespace scene

#endif