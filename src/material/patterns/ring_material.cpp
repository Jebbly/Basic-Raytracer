#include "material/patterns/ring_material.h"

// raytrace functions
image::Color material::pattern::RingMaterial::pattern(const math::Tuple4d &point) const
{
    if (((int) floor(sqrt(pow(point(0), 2) + pow(point(2), 2))) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}
