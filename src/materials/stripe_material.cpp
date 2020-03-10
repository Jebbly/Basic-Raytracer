#include "materials/stripe_material.h"

StripeMaterial::StripeMaterial(const Tuple &color_a, const Tuple &color_b, double ambient, double diffuse, double specular, double shininess) :
    Material{ambient, diffuse, specular, shininess},
    m_color_a{color_a},
    m_color_b{color_b}
{}

// accessor methods
const Tuple& StripeMaterial::get_color(const Tuple& pos) const
{
    if (((int) pos.get(0) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}