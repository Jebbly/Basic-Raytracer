#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "materials/color_material.h"
#include "primitives/primitive.h"

class Triangle : public Primitive
{
private:
    // attributes
    Tuple m_points[3];
    Tuple m_edges[2];
    Tuple m_normal;

public:
    Triangle(const Tuple &point1, const Tuple &point2, const Tuple &point3);

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif