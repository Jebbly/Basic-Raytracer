#include "materials/color_material.h"

ColorMaterial::ColorMaterial(const Tuple &color, double ambient, double diffuse, double specular, double shininess, double reflective) :
    Material{ambient, diffuse, specular, shininess, reflective},
    m_color{color}
{}

// accessor methods
Tuple ColorMaterial::get_color(const Tuple &pos) const
{
    return m_color;
}