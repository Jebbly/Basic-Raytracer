#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "math/tuple.h"
#include "core/computation.h"
#include "image/color.h"
#include "scene/lights/light.h"

namespace scene::light
{

class PointLight : public Light
{
private:
    // attributes
    math::Tuple4d m_position;

public:
    PointLight(const image::Color &intensity, const math::Tuple4d &position);

    // accessor methods
    virtual const math::Tuple4d direction(const math::Tuple4d &point) const override;

    // raytrace functions
    virtual const image::Color lighting(const core::Computation &comp) const override;
};

} // namespace scene::light

#endif
