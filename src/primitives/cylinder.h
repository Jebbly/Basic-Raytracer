#ifndef CYLINDER_H
#define CYLINDER_H

#include <cmath>
#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "materials/material.h"
#include "materials/color_material.h"
#include "primitives/primitive.h"

class Cylinder : public Primitive
{
private:
    // attributes
    double m_minmax[2];
    bool m_closed;

    // helper function
    void intersect_caps(const Ray &r, std::vector<Intersection> &xs) const;

public:
    Cylinder(const Matrix &transformation = identity(), Material *material = &(ColorMaterial{}), double minimum = -INFINITY, double maximum = INFINITY, bool closed = false);

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;
};

#endif