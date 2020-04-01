#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Sphere : public Primitive
{
public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif