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
protected:
    // primitive-specific ray intersect functions
    virtual Tuple local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;

public:
    Sphere(const Matrix &transformation = identity(), const Material &material = Material{});
};

#endif