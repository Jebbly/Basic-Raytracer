#include "material/color_material.h"

material::ColorMaterial::ColorMaterial(const image::Color &color, double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) :
    Material{ambient, diffuse, specular, shininess, reflective, transparency, IOR},
    m_color{color}
{}

// accessor methods
image::Color material::ColorMaterial::color(const math::Tuple4d &point) const
{
    return m_color;
}
