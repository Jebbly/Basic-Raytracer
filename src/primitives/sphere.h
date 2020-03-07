#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/material.h"
#include "primitives/primitive.h"

class Sphere : public Primitive
{
public:
    Sphere(const Matrix &transformation = identity(), const Material &material = Material{});

    // ray intersect functions
    Tuple intersect(const Ray &r) const override;
    Tuple normal(const Tuple &t) const override;
};

#endif