#ifndef SMOOTH_TRIANGLE_H
#define SMOOTH_TRIANGLE_H

#include <cassert>
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
#include "primitives/triangle.h"

class SmoothTriangle : public Triangle
{
private:
    // smooth shading attributes
    Tuple m_normals[3];

public:
    SmoothTriangle(const Tuple &point1, const Tuple &point2, const Tuple &point3, const Tuple &normal1, const Tuple &normal2, const Tuple &normal3);

    // accessor methods
    const Tuple& get_normal(int index) const;

    // ray intersect functions
    using Triangle::local_intersect;
    virtual Tuple local_normal(const Tuple &t, const Intersection &hit) const override;
};

#endif