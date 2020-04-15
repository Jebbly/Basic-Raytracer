#include "material/patterns/pattern.h"

material::pattern::Pattern::Pattern(const image::Color &color_a, const image::Color &color_b, const math::Matrix4d &transformation, double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) :
    Material{ambient, diffuse, specular, shininess, reflective, transparency, IOR},
    m_color_a{color_a},
    m_color_b{color_b},
    m_transformation{transformation}
{}

// accessor methods
void material::pattern::Pattern::set_transformation(const math::Matrix4d &transformation)
{
    m_transformation = transformation;
}

// raytrace functions
image::Color material::pattern::Pattern::color(const math::Tuple4d &point) const
{
    return pattern(m_transformation.inverse() * point);
}
