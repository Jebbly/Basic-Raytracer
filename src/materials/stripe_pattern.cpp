#include "materials/stripe_pattern.h"

StripePattern::StripePattern(const Tuple &m_color_a, const Tuple &m_color_b) :
    Pattern{m_color_a, m_color_b}
{}

// accessor methods
const Tuple& StripePattern::get_color(const Tuple& pos) const
{
    if (((int) pos.get(0) % 2) == 0)
	return m_color_a;
    else
	return m_color_b;
}