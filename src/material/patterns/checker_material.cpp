#include "material/patterns/checker_material.h"

// raytrace functions
image::Color material::pattern::CheckerMaterial::pattern(const math::Tuple4d &point) const
{
    if ((((int) floor(point(0) + constants::EPSILON) + (int) floor(point(1) + constants::EPSILON) + (int) floor(point(2) + constants::EPSILON)) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}
