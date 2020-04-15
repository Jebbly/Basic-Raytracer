#ifndef LIGHTING_H
#define LIGHTING_H

#include <cmath>
#include <memory>
#include "math/tuple.h"
#include "core/computation.h"
#include "image/color.h"
#include "geometry/primitives/primitive.h"
#include "material/material.h"

namespace scene::light
{

class Light
{
protected:
    // attributes
    image::Color m_intensity;

    Light(const image::Color &intensity);

    // phong shading
    const image::Color phong_shading(geometry::primitive::Primitive *object, const math::Tuple4d &position, const math::Tuple4d &eye, const math::Tuple4d &normal) const;

public:
    // accessor methods
    virtual const math::Tuple4d direction(const math::Tuple4d &point) const = 0;

    // raytrace functions
    virtual const image::Color lighting(const core::Computation &comp) const = 0;
};

} // namespace scene::light

#endif
