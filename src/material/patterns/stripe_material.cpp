#include "material/patterns/stripe_material.h"

// raytrace functions
image::Color material::pattern::StripeMaterial::pattern(const math::Tuple4d& point) const
{
    if (((int) floor(point(0) + constants::EPSILON) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}
