#ifndef STRIPE_MATERIAL_H
#define STRIPE_MATERIAL_H

#include "math/tuple.h"
#include "image/color.h"
#include "material/material.h"
#include "material/patterns/pattern.h"

namespace material::pattern
{

class StripeMaterial : public Pattern
{
public:
    using Pattern::Pattern;

    // raytrace functions
    virtual image::Color get_pattern(const math::Tuple4d &pos) const override;
};

} // namespace material::pattern

#endif