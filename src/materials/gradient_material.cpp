#include "materials/gradient_material.h"

// raytrace functions
Tuple GradientMaterial::get_pattern(const Tuple &pos) const
{
    Tuple diff = m_color_b - m_color_a;
    double fraction = pos.get(0) - (int) pos.get(0);
    return (m_color_a + diff * fraction);
}