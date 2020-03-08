#ifndef PLANE_H
#define PLANE_H

#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Plane : public Primitive
{
public:
    Plane(const Matrix &transformation = identity(), const Material &material = Material{});

    // ray intersect functions
    virtual Tuple local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;
};

#endif