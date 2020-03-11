#include "scene/point_light.h"

PointLight::PointLight(const Tuple &intensity, const Tuple &position) :
    Light{intensity},
    m_position{position}
{}

// accessor methods
const Tuple PointLight::get_direction(const Tuple &t) const
{
    return normalize(m_position - t);
}

// raytrace functions
const Tuple PointLight::lighting(const Computation &comp) const
{
    Tuple color_value = phong_shading(comp.get_object(), comp.get_point(), comp.get_eye(), comp.get_normal());
    double distance = magnitude(comp.get_point() - m_position);
    return color_value / (1 + 0.01 * pow(distance, 2));
}