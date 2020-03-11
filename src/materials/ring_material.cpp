#include "materials/ring_material.h"

RingMaterial::RingMaterial(const Tuple &color_a, const Tuple &color_b, const Matrix &transformation, double ambient, double diffuse, double specular, double shininess) :
    Pattern{color_a, color_b, transformation, ambient, diffuse, specular, shininess}
{}

// raytrace functions
Tuple RingMaterial::get_pattern(const Tuple &pos) const
{
    if (((int) sqrt(pow(pos.get(0), 2) + pow(pos.get(2), 2)) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}