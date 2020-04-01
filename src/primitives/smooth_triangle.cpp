#include "primitives/smooth_triangle.h"

SmoothTriangle::SmoothTriangle(const Tuple &point1, const Tuple &point2, const Tuple &point3, const Tuple &normal1, const Tuple &normal2, const Tuple &normal3) :
    Triangle{point1, point2, point3},
    m_normals{normal1, normal2, normal3}
{}

// accessor methods
const Tuple& SmoothTriangle::get_normal(int index) const
{
    assert(index < 3 && "index out of bounds");
    return m_normals[index];
}

// ray intersect functions
Tuple SmoothTriangle::local_normal(const Tuple &t, const Intersection &hit) const
{
    double u = hit.get_uv().first, v = hit.get_uv().second;
    return m_normals[1] * u + m_normals[2] * v + m_normals[0] * (1 - u - v);
}