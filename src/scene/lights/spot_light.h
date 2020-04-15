#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <algorithm>
#include "math/tuple.h"
#include "core/computation.h"
#include "image/color.h"
#include "scene/lights/light.h"

namespace scene::light
{

class SpotLight : public Light
{
private:
    // attributes
    math::Tuple4d m_position, m_direction;
    double m_outer_cutoff, m_inner_cutoff;

public:
    SpotLight(const image::Color &intensity, const math::Tuple4d &position, const math::Tuple4d &direction, double outer_cutoff, double inner_cutoff);

    // accessor methods
    virtual const math::Tuple4d direction(const math::Tuple4d &point) const override;

    // raytrace functions
    virtual const image::Color lighting(const core::Computation &comp) const override;
};

} // namespace scene::light

#endif
