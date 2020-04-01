#include "primitives/triangle.h"

Triangle::Triangle(const Tuple &point1, const Tuple &point2, const Tuple &point3) :
    Primitive{},
    m_points{point1, point2, point3},
    m_edges{point2 - point1, point3 - point1}
{
    m_normal = normalize(cross(m_edges[0], m_edges[1]));
}

// accessor methods
const Tuple& Triangle::get_point(int index) const
{
    assert(index < 3 && "index out of bounds");
    return m_points[index];
}

const Tuple& Triangle::get_edge(int index) const
{
    assert(index < 2 && "index out of bounds");
    return m_edges[index];
}

// ray intersect functions
std::vector<Intersection> Triangle::local_intersect(const Ray &r) const
{
    Tuple dir_cross_e2 = cross(r.get_direction(), m_edges[1]);
    double det = dot(m_edges[0], dir_cross_e2);

    std::vector<Intersection> intersects;
    if (abs(det) >= Constants::EPSILON)
    {
	double f = 1 / det;
	Tuple p1_to_origin = r.get_origin() - m_points[0];
	double u = f * dot(p1_to_origin, dir_cross_e2);
	if (u >= 0 && u <= 1)
	{
	    Tuple origin_cross_e1 = cross(p1_to_origin, m_edges[0]);
	    double v = f * dot(r.get_direction(), origin_cross_e1);
	    if (v >= 0 && (u + v) <= 1)
	    {
		double t = f * dot(m_edges[1], origin_cross_e1);
		intersects.push_back(Intersection{t, (Primitive*) this, std::make_pair(u, v)});
	    }
	}
    }
    return intersects;
}

Tuple Triangle::local_normal(const Tuple &t, const Intersection &hit) const
{
    return m_normal;
}

// utility functions
BoundingBox Triangle::local_bounds() const
{
    BoundingBox ret{};
    for (int i = 0; i < 3; i++)
    {
	ret.add_point(m_points[i]);
    }
    return ret;
}