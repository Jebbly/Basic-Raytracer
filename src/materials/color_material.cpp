#include "materials/color_material.h"

ColorMaterial::ColorMaterial(const Tuple &color, double ambient, double diffuse, double specular, double shininess) :
    Material{ambient, diffuse, specular, shininess},
    m_color{color}
{}

// accessor methods
const Tuple& ColorMaterial::get_color(const Tuple &pos) const
{
    return m_color;
}