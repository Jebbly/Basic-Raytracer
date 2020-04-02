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
    math::Tuple4d m_normals[3];

public:
    SmoothTriangle(const math::Tuple4d &point1, const math::Tuple4d &point2, const math::Tuple4d &point3, const math::Tuple4d &normal1, const math::Tuple4d &normal2, const math::Tuple4d &normal3);

    // accessor methods
    const math::Tuple4d& get_normal(int index) const;

    // ray intersect functions
    using Triangle::local_intersect;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;
};

#endif