#include "materials/stripe_material.h"

// raytrace functions
Tuple StripeMaterial::get_pattern(const Tuple& pos) const
{
    if (((int) floor(pos.get(0) + Constants::EPSILON) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}