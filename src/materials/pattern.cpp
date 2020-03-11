#include "materials/pattern.h"

Pattern::Pattern(const Tuple &color_a, const Tuple &color_b, const Matrix &transformation, double ambient, double diffuse, double specular, double shininess) :
    Material{ambient, diffuse, specular, shininess},
    m_color_a{color_a},
    m_color_b{color_b},
    m_transformation{transformation}
{}

// accessor methods
void Pattern::set_transformation(const Matrix &transformation)
{
    m_transformation = transformation;
}

// raytrace functions
const Tuple& Pattern::get_color(const Tuple &pos) const
{
    return get_pattern(multiply(m_transformation.inverse(), pos));
}