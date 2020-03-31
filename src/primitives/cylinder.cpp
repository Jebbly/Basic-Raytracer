#include "primitives/cylinder.h"

Cylinder::Cylinder(const Matrix &transformation, std::shared_ptr<Material> material, double minimum, double maximum, bool closed) :
    Primitive(transformation, material),
    m_minmax{minimum, maximum},
    m_closed{closed}
{}

// ray intersect functions
std::vector<Intersection> Cylinder::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    Tuple origin = r.get_origin();
    Tuple direction = r.get_direction();
    
    double a = pow(direction.get(0), 2) + pow(direction.get(2), 2);
    if (a < Constants::EPSILON)
	return intersects;

    double b = 2 * (origin.get(0) * direction.get(0) + origin.get(2) * direction.get(2));
    double c = pow(origin.get(0), 2) + pow(origin.get(2), 2) - 1;

    double discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant < 0)
	return intersects;

    for (int i = 0; i < 2; i++)
    {
	double t = (-b + (2 * i - 1) * sqrt(discriminant)) / (2 * a);
	double y = origin.get(1) + direction.get(1) * t;
	if (y > m_minmax[0] && y < m_minmax[1])
	    intersects.push_back(Intersection{t, (Primitive*) this});
    }

    if (m_closed && !(abs(r.get_direction().get(1)) < Constants::EPSILON))
    {
	Tuple radii = intersect_caps(r, m_minmax);
	for (int i = 0; i < 2; i++)
	{
	    if (radii.get(2 * i) <= 1)
		intersects.push_back(Intersection{radii.get(2 * i + 1), (Primitive*) this});
	}
    }

    return intersects;
}

Tuple Cylinder::local_normal(const Tuple &t) const
{
    double distance = pow(t.get(0), 2) + pow(t.get(2), 2);
    if (m_closed && distance + Constants::EPSILON < 1)
    {
	if (t.get(1) >= (m_minmax[1] - Constants::EPSILON))
	    return vector(0, 1, 0);
	else
	    return vector(0, -1, 0);
    }
    return vector(t.get(0), 0, t.get(2));
}

// utility functions
BoundingBox Cylinder::local_bounds() const
{
    return BoundingBox{point(-1, m_minmax[0], -1), point(1, m_minmax[1], 1)};
}