#include "material/color_material.h"

material::ColorMaterial::ColorMaterial(const math::Tuple3d &color, double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) :
    Material{ambient, diffuse, specular, shininess, reflective, transparency, IOR},
    m_color{color}
{}

// accessor methods
math::Tuple3d material::ColorMaterial::get_color(const math::Tuple4d &pos) const
{
    return m_color;
}