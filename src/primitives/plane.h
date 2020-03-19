#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Plane : public Primitive
{
public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<double> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;
};

#endif