#include "materials/patterns/ring_material.h"

// raytrace functions
math::Tuple3d material::pattern::RingMaterial::get_pattern(const math::Tuple4d &pos) const
{
    if (((int) floor(sqrt(pow(pos(0), 2) + pow(pos(2), 2))) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}