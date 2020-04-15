#include "scene/lights/directional_light.h"

scene::light::DirectionalLight::DirectionalLight(const image::Color &intensity, const math::Tuple4d &direction) :
    Light{intensity},
    m_direction{-direction.normalize()}
{}

// accessor methods
const math::Tuple4d scene::light::DirectionalLight::get_direction(const math::Tuple4d &t) const
{
    return m_direction;
}

// raytrace functions
const image::Color scene::light::DirectionalLight::lighting(const core::Computation &comp) const
{
    return phong_shading(comp.get_object(), comp.get_point(), comp.get_eye(), comp.get_normal());
}