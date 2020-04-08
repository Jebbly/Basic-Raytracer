#ifndef LIGHTING_H
#define LIGHTING_H

#include <cmath>
#include "math/tuple.h"
#include "core/computation.h"
#include "materials/material.h"

namespace scene::light
{

class Light
{
protected:
    // attributes
    math::Tuple3d m_intensity;

    Light(const math::Tuple3d &intensity);

    // phong shading
    const math::Tuple3d phong_shading(geometry::primitive::Primitive *object, const math::Tuple4d &position, const math::Tuple4d &eye, const math::Tuple4d &normal) const;

public:
    // accessor methods
    const math::Tuple3d& get_intensity() const {return m_intensity;}
    virtual const math::Tuple4d get_direction(const math::Tuple4d &t) const = 0;

    // raytrace functions
    virtual const math::Tuple3d lighting(const core::Computation &comp) const = 0;
};

} // namespace scene::light

#endif