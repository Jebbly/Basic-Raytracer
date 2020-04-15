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
    image::Color m_ambient;
    std::vector<light::Light*> m_lights;
    std::vector<geometry::primitive::Primitive*> m_objects;

public:
    World(const image::Color &ambient = image::Color{1, 1, 1});

    // accessor methods
    std::vector<light::Light*>& get_lights() {return m_lights;}
    std::vector<geometry::primitive::Primitive*>& get_objects() {return m_objects;}

    void add_object(geometry::primitive::Primitive &object);
    void add_light(light::Light &light);

    // raytrace functions
    std::vector<core::Intersection> intersects(const core::Ray &ray) const;
    bool shadow(const light::Light *light, const math::Tuple4d &position) const;
    image::Color reflection(const core::Computation &comp, int recursion_depth) const;
    image::Color refraction(const core::Computation &comp, int recursion_depth) const;
    double schlick(const core::Computation &comp) const;
    image::Color shade(const core::Computation &comp, int recursion_depth) const;
    image::Color final_color(const core::Ray &ray, int recursion_depth) const;
};

} // namespace scene

#endif