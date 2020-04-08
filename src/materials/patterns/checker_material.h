#ifndef CHECKER_MATERIAL_H
#define CHECKER_MATERIAL_H

#include "math/tuple.h"
#include "materials/material.h"
#include "materials/patterns/pattern.h"

namespace material::pattern
{

class CheckerMaterial : public Pattern
{
public:
    using Pattern::Pattern;

    // raytrace functions
    virtual math::Tuple3d get_pattern(const math::Tuple4d &pos) const override;
};

} // namespace material::pattern

#endif