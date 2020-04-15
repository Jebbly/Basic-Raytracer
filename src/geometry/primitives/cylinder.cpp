#include "geometry/primitives/cylinder.h"

geometry::primitive::Cylinder::Cylinder(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material, double minimum, double maximum, bool closed) :
    Primitive(transformation, material),
    m_minmax{minimum, maximum},
    m_closed{closed}
{}

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Cylinder::local_intersect(const core::Ray &ray) const
{
    std::vector<core::Intersection> intersects;

    math::Tuple4d origin = ray.origin();
    math::Tuple4d direction = ray.direction();
    
    double a = pow(direction(0), 2) + pow(direction(2), 2);
    if (a < constants::EPSILON)
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
	    intersects.push_back(core::Intersection{t, (Primitive*) this});
    }

    if (m_closed && !(std::abs(ray.direction()(1)) < constants::EPSILON))
    {
	std::array<std::pair<double, double>, 2> radii = utility::intersect_caps(ray, m_minmax);
	for (int i = 0; i < 2; i++)
	{
	    if (radii[i].first <= 1)
		intersects.push_back(core::Intersection{radii[i].second, (Primitive*) this});
	}
    }

    return intersects;
}

math::Tuple4d geometry::primitive::Cylinder::local_normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    double distance = pow(point(0), 2) + pow(point(2), 2);
    if (m_closed && distance + constants::EPSILON < 1)
    {
	if (point(1) >= (m_minmax[1] - constants::EPSILON))
	    return math::vector(0, 1, 0);
	else
	    return math::vector(0, -1, 0);
    }
    return math::vector(point(0), 0, point(2));
}

// utility functions
core::BoundingBox geometry::primitive::Cylinder::local_bounds() const
{
    return core::BoundingBox{math::point(-1, m_minmax[0], -1), math::point(1, m_minmax[1], 1)};
}
