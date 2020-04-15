#include "scene/lights/spot_light.h"

scene::light::SpotLight::SpotLight(const image::Color &intensity, const math::Tuple4d &position, const math::Tuple4d &direction, double outer_cutoff, double inner_cutoff) :
    Light{intensity},
    m_position{position},
    m_direction{direction.normalize()},
    m_outer_cutoff{outer_cutoff},
    m_inner_cutoff{inner_cutoff}
{}

// accessor methods
const math::Tuple4d scene::light::SpotLight::direction(const math::Tuple4d &point) const
{
    return (m_position - point).normalize();
}

// raytrace functions
const image::Color scene::light::SpotLight::lighting(const core::Computation &comp) const
{
    double theta = dot(-m_direction, direction(comp.point()));
    double intensity = std::clamp((theta - m_outer_cutoff) / (m_inner_cutoff - m_outer_cutoff), 0.0, 1.0);
    return phong_shading(comp.object(), comp.point(), comp.eye(), comp.normal()) * intensity;
}
