#include "materials/ring_material.h"

// raytrace functions
Tuple RingMaterial::get_pattern(const Tuple &pos) const
{
    if (((int) floor(sqrt(pow(pos.get(0), 2) + pow(pos.get(2), 2))) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}