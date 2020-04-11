#ifndef GRADIENT_MATERIAL_H
#define GRADIENT_MATERIAL_H

#include "math/tuple.h"
#include "material/material.h"
#include "material/patterns/pattern.h"

namespace material::pattern
{

class GradientMaterial : public Pattern
{
public:
    using Pattern::Pattern;

    // raytrace functions
    virtual math::Tuple3d get_pattern(const math::Tuple4d &pos) const override;
};

} // namespace material::pattern

#endif