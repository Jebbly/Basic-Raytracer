#ifndef SMOOTH_TRIANGLE_H
#define SMOOTH_TRIANGLE_H

#include <cassert>
#include <cmath>
#include <vector>
#include "math/tuple.h"
#include "core/bounding_box.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "geometry/primitives/primitive.h"
#include "geometry/primitives/triangle.h"

namespace geometry::primitive
{

class SmoothTriangle : public Triangle
{
private:
    // smooth shading attributes
    math::Tuple4d m_normals[3];

public:
    SmoothTriangle(const math::Tuple4d &point1, const math::Tuple4d &point2, const math::Tuple4d &point3, const math::Tuple4d &normal1, const math::Tuple4d &normal2, const math::Tuple4d &normal3);

    // ray intersect functions
    using Triangle::local_intersect;
    virtual math::Tuple4d local_normal(const math::Tuple4d &point, const core::Intersection &hit) const override;
};

} // namespace geometry::primitive

#endif
