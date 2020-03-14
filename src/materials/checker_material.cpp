#include "materials/checker_material.h"

// raytrace functions
Tuple CheckerMaterial::get_pattern(const Tuple &pos) const
{
    if ((((int) pos.get(0) + (int) pos.get(1) + (int) pos.get(2)) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}