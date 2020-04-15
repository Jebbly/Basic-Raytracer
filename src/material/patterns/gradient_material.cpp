#include "material/patterns/gradient_material.h"

// raytrace functions
image::Color material::pattern::GradientMaterial::pattern(const math::Tuple4d &point) const
{
    image::Color diff = m_color_b - m_color_a;
    double fraction = point(0) - (int) point(0);
    return (m_color_a + diff * fraction);
}
