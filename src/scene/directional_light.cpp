#include "scene/directional_light.h"

DirectionalLight::DirectionalLight(const math::Tuple3d &intensity, const math::Tuple4d &direction) :
    Light{intensity},
    m_direction{-direction.normalize()}
{}

// accessor methods
const math::Tuple4d DirectionalLight::get_direction(const math::Tuple4d &t) const
{
    return m_direction;
}

// raytrace functions
const math::Tuple3d DirectionalLight::lighting(const Computation &comp) const
{
    return phong_shading(comp.get_object(), comp.get_point(), comp.get_eye(), comp.get_normal());
}