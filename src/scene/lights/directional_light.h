#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "math/tuple.h"
#include "core/computation.h"
#include "scene/lights/light.h"

namespace scene::light
{

class DirectionalLight : public Light
{
private:
    // attributes
    math::Tuple4d m_direction;

public:
    DirectionalLight(const image::Color &intensity, const math::Tuple4d &direction);

    // accessor methods
    virtual const math::Tuple4d get_direction(const math::Tuple4d &t) const override;

    // raytrace functions
    virtual const image::Color lighting(const core::Computation &comp) const override;
};

}

#endif