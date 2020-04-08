#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "geometry/primitives/primitive.h"

namespace geometry::primitive
{

class Sphere : public Primitive
{
public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

} // namespace geometry::primitive

#endif