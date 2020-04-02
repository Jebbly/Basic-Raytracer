#ifndef RING_MATERIAL_H
#define RING_MATERIAL_H

#include <cmath>
#include "math/tuple.h"
#include "materials/material.h"
#include "materials/pattern.h"

class RingMaterial : public Pattern
{
public:
    using Pattern::Pattern;

    // raytrace functions
    virtual math::Tuple3d get_pattern(const math::Tuple4d &pos) const override;
};

#endif