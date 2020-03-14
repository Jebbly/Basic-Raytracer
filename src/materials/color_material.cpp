#include "materials/color_material.h"

ColorMaterial::ColorMaterial(const Tuple &color, double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) :
    Material{ambient, diffuse, specular, shininess, reflective, transparency, IOR},
    m_color{color}
{}

// accessor methods
Tuple ColorMaterial::get_color(const Tuple &pos) const
{
    return m_color;
}