#include "materials/patterns/gradient_material.h"

// raytrace functions
math::Tuple3d material::pattern::GradientMaterial::get_pattern(const math::Tuple4d &pos) const
{
    math::Tuple3d diff = m_color_b - m_color_a;
    double fraction = pos(0) - (int) pos(0);
    return (m_color_a + diff * fraction);
}