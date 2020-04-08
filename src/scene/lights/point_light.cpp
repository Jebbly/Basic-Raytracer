#include "scene/lights/point_light.h"

scene::light::PointLight::PointLight(const math::Tuple3d &intensity, const math::Tuple4d &position) :
    Light{intensity},
    m_position{position}
{}

// accessor methods
const math::Tuple4d scene::light::PointLight::get_direction(const math::Tuple4d &t) const
{
    return (m_position - t).normalize();
}

// raytrace functions
const math::Tuple3d scene::light::PointLight::lighting(const core::Computation &comp) const
{
    math::Tuple3d color_value = phong_shading(comp.get_object(), comp.get_point(), comp.get_eye(), comp.get_normal());
    double distance = (comp.get_point() - m_position).magnitude();
    return color_value / (1 + 0.01 * pow(distance, 2));
}