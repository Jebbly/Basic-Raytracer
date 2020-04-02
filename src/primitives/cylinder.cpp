#include "primitives/cylinder.h"

Cylinder::Cylinder(const math::Matrix4d &transformation, std::shared_ptr<Material> material, double minimum, double maximum, bool closed) :
    Primitive(transformation, material),
    m_minmax{minimum, maximum},
    m_closed{closed}
{}

// ray intersect functions
std::vector<Intersection> Cylinder::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    math::Tuple4d origin = r.get_origin();
    math::Tuple4d direction = r.get_direction();
    
    double a = pow(direction(0), 2) + pow(direction(2), 2);
    if (a < Constants::EPSILON)
	return intersects;

    double b = 2 * (origin(0) * direction(0) + origin(2) * direction(2));
    double c = pow(origin(0), 2) + pow(origin(2), 2) - 1;

    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
	return intersects;

    for (int i = 0; i < 2; i++)
    {
	double t = (-b + (2 * i - 1) * sqrt(discriminant)) / (2 * a);
	double y = origin(1) + direction(1) * t;
	if (y > m_minmax[0] && y < m_minmax[1])
	    intersects.push_back(Intersection{t, (Primitive*) this});
    }

    if (m_closed && !(abs(r.get_direction()(1)) < Constants::EPSILON))
    {
	math::Tuple4d radii = intersect_caps(r, m_minmax);
	for (int i = 0; i < 2; i++)
	{
	    if (radii(2 * i) <= 1)
		intersects.push_back(Intersection{radii(2 * i + 1), (Primitive*) this});
	}
    }

    return intersects;
}

math::Tuple4d Cylinder::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    double distance = pow(t(0), 2) + pow(t(2), 2);
    if (m_closed && distance + Constants::EPSILON < 1)
    {
	if (t(1) >= (m_minmax[1] - Constants::EPSILON))
	    return math::vector<double>(0, 1, 0);
	else
	    return math::vector<double>(0, -1, 0);
    }
    return math::vector<double>(t(0), 0, t(2));
}

// utility functions
BoundingBox Cylinder::local_bounds() const
{
    return BoundingBox{math::point<double>(-1, m_minmax[0], -1), math::point<double>(1, m_minmax[1], 1)};
}