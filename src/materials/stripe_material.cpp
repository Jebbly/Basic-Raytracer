#include "materials/stripe_material.h"

// raytrace functions
math::Tuple3d StripeMaterial::get_pattern(const math::Tuple4d& pos) const
{
    if (((int) floor(pos(0) + Constants::EPSILON) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}