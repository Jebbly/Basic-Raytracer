#include "material/patterns/stripe_material.h"

// raytrace functions
image::Color material::pattern::StripeMaterial::get_pattern(const math::Tuple4d& pos) const
{
    if (((int) floor(pos(0) + constants::EPSILON) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}