#include "primitives/cone.h"

Cone::Cone(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material, double minimum, double maximum, bool closed) :
    Primitive(transformation, material),
    m_minmax{minimum, maximum},
    m_closed{closed}
{}

// ray intersect functions
std::vector<Intersection> Cone::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    math::Tuple4d origin = r.get_origin();
    math::Tuple4d direction = r.get_direction();

    double a = pow(direction(0), 2) - pow(direction(1), 2) + pow(direction(2), 2);
    double b = 2 * (origin(0) * direction(0) - origin(1) * direction(1) + origin(2) * direction(2));
    double c = pow(origin(0), 2) - pow(origin(1), 2) + pow(origin(2), 2);

    if (a < constants::EPSILON)
    {
	if (b >= constants::EPSILON)
	    intersects.push_back(Intersection{-c / (2 * b), (Primitive*) this});
	return intersects;
    }

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

    if (m_closed && !(abs(r.get_direction()(1)) < constants::EPSILON))
    {
	math::Tuple4d radii = utility::intersect_caps(r,  m_minmax);
	for (int i = 0; i < 2; i++)
	{
	    if (radii(2 * i) <= abs(m_minmax[i]))
		intersects.push_back(Intersection{radii(2 * i + 1), (Primitive*) this});
	}
    }

    return intersects;
}

math::Tuple4d Cone::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    double distance = pow(t(0), 2) + pow(t(2), 2);
    if (m_closed &&
	distance + constants::EPSILON < abs(m_minmax[1]) &&
	t(1) >= m_minmax[1] - constants::EPSILON)
	return math::vector<double>(0, 1, 0);
    else if (m_closed &&
	     distance + constants::EPSILON < abs(m_minmax[0]) &&
	     t(1) <= m_minmax[0] + constants::EPSILON)
	return math::vector<double>(0, -1, 0);

    double y = sqrt(distance) * (t(1) > 0) ? -1 : 1;
    return math::vector<double>(t(0), y, t(2));
}

// utility functions
BoundingBox Cone::local_bounds() const
{
    double a = abs(m_minmax[0]);
    double b = abs(m_minmax[1]);
    double limit = std::max(a, b);

    return BoundingBox{math::point<double>(-limit, m_minmax[0], -limit), math::point<double>(limit, m_minmax[1], limit)};
}