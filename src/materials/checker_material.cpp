#include "materials/checker_material.h"

// raytrace functions
Tuple CheckerMaterial::get_pattern(const Tuple &pos) const
{
    if ((((int) floor(pos.get(0) + Constants::EPSILON) + (int) floor(pos.get(1) + Constants::EPSILON) + (int) floor(pos.get(2) + Constants::EPSILON)) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}