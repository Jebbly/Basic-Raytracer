#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include <vector>
#include "utility/common.h"
#include "utility/helper.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Cube : public Primitive
{
public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif