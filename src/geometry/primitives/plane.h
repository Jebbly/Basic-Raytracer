#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include <vector>
#include "math/tuple.h"
#include "core/bounding_box.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "geometry/primitives/primitive.h"
#include "material/material.h"

namespace geometry::primitive
{

class Plane : public Primitive
{
public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<core::Intersection> local_intersect(const core::Ray &ray) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &point, const core::Intersection &hit) const override;

    // utility functions
    virtual core::BoundingBox local_bounds() const override;
};

} // namespace geometry::primitive

#endif
