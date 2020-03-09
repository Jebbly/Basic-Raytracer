#ifndef STRIPE_PATTERN_H
#define STRIPE_PATTERN_H

#include "math/tuple.h"
#include "materials/pattern.h"

class StripePattern : public Pattern
{
public:
    StripePattern(const Tuple &m_color_a = color(0, 0, 0), const Tuple &m_color_b = color(1, 1, 1));

    // accessor methods
    virtual const Tuple& get_color(const Tuple &pos) const override;
};

#endif