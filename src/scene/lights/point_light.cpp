#include "scene/lights/point_light.h"

scene::light::PointLight::PointLight(const image::Color &intensity, const math::Tuple4d &position) :
    Light{intensity},
    m_position{position}
{}

// accessor methods
const math::Tuple4d scene::light::PointLight::direction(const math::Tuple4d &point) const
{
    return (m_position - point).normalize();
}

// raytrace functions
const image::Color scene::light::PointLight::lighting(const core::Computation &comp) const
{
    image::Color m_color_value = phong_shading(comp.object(), comp.point(), comp.eye(), comp.normal());
    double distance = (comp.point() - m_position).magnitude();
    return m_color_value / (1 + 0.01 * pow(distance, 2));
}
