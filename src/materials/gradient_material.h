#ifndef GRADIENT_MATERIAL_H
#define GRADIENT_MATERIAL_H

#include "math/tuple.h"
#include "materials/material.h"
#include "materials/pattern.h"

class GradientMaterial : public Pattern
{
public:
    using Pattern::Pattern;

    // raytrace functions
    virtual math::Tuple3d get_pattern(const math::Tuple4d &pos) const override;
};

#endif