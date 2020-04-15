#ifndef STRIPE_MATERIAL_H
#define STRIPE_MATERIAL_H

#include <cmath>
#include "utility/constants.h"
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
    virtual image::Color pattern(const math::Tuple4d &point) const override;
};

} // namespace material::pattern

#endif
