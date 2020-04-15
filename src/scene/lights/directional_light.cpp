#include "scene/lights/directional_light.h"

scene::light::DirectionalLight::DirectionalLight(const image::Color &intensity, const math::Tuple4d &direction) :
    Light{intensity},
    m_direction{-direction.normalize()}
{}

// accessor methods
const math::Tuple4d scene::light::DirectionalLight::direction(const math::Tuple4d &point) const
{
    return m_direction;
}

// raytrace functions
const image::Color scene::light::DirectionalLight::lighting(const core::Computation &comp) const
{
    return phong_shading(comp.object(), comp.point(), comp.eye(), comp.normal());
}
