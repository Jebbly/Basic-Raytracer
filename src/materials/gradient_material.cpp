#include "materials/gradient_material.h"

GradientMaterial::GradientMaterial(const Tuple &color_a, const Tuple &color_b, const Matrix &transformation, double ambient, double diffuse, double specular, double shininess) :
    Pattern{color_a, color_b, transformation, ambient, diffuse, specular, shininess}
{}

// raytrace functions
Tuple GradientMaterial::get_pattern(const Tuple &pos) const
{
    Tuple diff = m_color_b - m_color_a;
    double fraction = pos.get(0) - (int) pos.get(0);
    return (m_color_a + diff * fraction);
}