#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Cube : public Primitive
{
private:
    // helper function
    Tuple check_axis(double origin, double direction) const;

public:
    using Primitive::Primitive;

    // ray intersect functions
    virtual std::vector<double> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;
};

#endif