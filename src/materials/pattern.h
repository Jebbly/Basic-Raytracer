#ifndef PATTERN_H
#define PATTERN_H

#include "math/tuple.h"

class Pattern
{
protected:
    // attributes
    Tuple m_color_a, m_color_b;

    Pattern(const Tuple &color_a, const Tuple &color_b);

public:
    // accessor methods
    virtual const Tuple& get_pattern(const Tuple &pos) const = 0;
};

#endif