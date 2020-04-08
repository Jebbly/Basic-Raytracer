#include "geometry/primitives/smooth_triangle.h"

geometry::primitive::SmoothTriangle::SmoothTriangle(const math::Tuple4d &point1, const math::Tuple4d &point2, const math::Tuple4d &point3, const math::Tuple4d &normal1, const math::Tuple4d &normal2, const math::Tuple4d &normal3) :
    Triangle{point1, point2, point3},
    m_normals{normal1, normal2, normal3}
{}

// accessor methods
const math::Tuple4d& geometry::primitive::SmoothTriangle::get_normal(int index) const
{
    assert(index < 3 && "index out of bounds");
    return m_normals[index];
}

// ray intersect functions
math::Tuple4d geometry::primitive::SmoothTriangle::local_normal(const math::Tuple4d &t, const core::Intersection &hit) const
{
    double u = hit.get_uv().first, v = hit.get_uv().second;
    return m_normals[1] * u + m_normals[2] * v + m_normals[0] * (1 - u - v);
}