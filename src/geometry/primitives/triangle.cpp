#include "geometry/primitives/triangle.h"

geometry::primitive::Triangle::Triangle(const math::Tuple4d &point1, const math::Tuple4d &point2, const math::Tuple4d &point3) :
    Primitive{},
    m_points{point1, point2, point3},
    m_edges{point2 - point1, point3 - point1}
{
    m_normal = cross(m_edges[0], m_edges[1]).normalize();
}

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Triangle::local_intersect(const core::Ray &ray) const
{
    math::Tuple4d dir_cross_e2 = cross(ray.direction(), m_edges[1]);
    double det = dot(m_edges[0], dir_cross_e2);

    std::vector<core::Intersection> intersects;
    if (std::abs(det) >= constants::EPSILON)
    {
	double f = 1 / det;
	math::Tuple4d p1_to_origin = ray.origin() - m_points[0];
	double u = f * dot(p1_to_origin, dir_cross_e2);
	if (u >= 0 && u <= 1)
	{
	    math::Tuple4d origin_cross_e1 = cross(p1_to_origin, m_edges[0]);
	    double v = f * dot(ray.direction(), origin_cross_e1);
	    if (v >= 0 && (u + v) <= 1)
	    {
		double t = f * dot(m_edges[1], origin_cross_e1);
		intersects.push_back(core::Intersection{t, (Primitive*) this, std::make_pair(u, v)});
	    }
	}
    }
    return intersects;
}

math::Tuple4d geometry::primitive::Triangle::local_normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    return m_normal;
}

// utility functions
core::BoundingBox geometry::primitive::Triangle::local_bounds() const
{
    core::BoundingBox ret{};
    for (int i = 0; i < 3; i++)
    {
	ret.add_point(m_points[i]);
    }
    return ret;
}
