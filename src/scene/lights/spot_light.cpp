#include "scene/lights/spot_light.h"

scene::light::SpotLight::SpotLight(const math::Tuple3d &intensity, const math::Tuple4d &position, const math::Tuple4d &direction, double outer_cutoff, double inner_cutoff) :
    Light{intensity},
    m_position{position},
    m_direction{direction.normalize()},
    m_outer_cutoff{outer_cutoff},
    m_inner_cutoff{inner_cutoff}
{}

// accessor methods
const math::Tuple4d scene::light::SpotLight::get_direction(const math::Tuple4d &t) const
{
    return (m_position - t).normalize();
}

// raytrace functions
const math::Tuple3d scene::light::SpotLight::lighting(const Computation &comp) const
{
    double theta = dot(-m_direction, get_direction(comp.get_point()));
    double intensity = std::clamp((theta - m_outer_cutoff) / (m_inner_cutoff - m_outer_cutoff), 0.0, 1.0);
    return phong_shading(comp.get_object(), comp.get_point(), comp.get_eye(), comp.get_normal()) * intensity;
}
