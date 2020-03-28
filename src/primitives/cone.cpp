#include "primitives/cone.h"

Cone::Cone(const Matrix &transformation, Material *material, double minimum, double maximum, bool closed) :
    Primitive(transformation, material),
    m_minmax{minimum, maximum},
    m_closed{closed}
{}

// helper function
void Cone::intersect_caps(const Ray &r, std::vector<Intersection> &xs) const
{
    double y_direction = r.get_direction().get(1);
    if (!m_closed || abs(y_direction) < Constants::EPSILON)
	return;

    double y_origin = r.get_origin().get(1);
    for (int i = 0; i < 2; i++)
    {
	double t = (m_minmax[i] - y_origin) / y_direction;
	Tuple pos = r.position(t);
	if (sqrt(pow(pos.get(0), 2) + pow(pos.get(2), 2)) <= abs(m_minmax[i]))
	    xs.push_back(Intersection{t, (Primitive*) this});
    }
}

// ray intersect functions
std::vector<Intersection> Cone::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    Tuple origin = r.get_origin();
    Tuple direction = r.get_direction();

    double a = pow(direction.get(0), 2) - pow(direction.get(1), 2) + pow(direction.get(2), 2);
    double b = 2 * (origin.get(0) * direction.get(0) - origin.get(1) * direction.get(1) + origin.get(2) * direction.get(2));
    double c = pow(origin.get(0), 2) - pow(origin.get(1), 2) + pow(origin.get(2), 2);

    if (a < Constants::EPSILON)
    {
	if (b >= Constants::EPSILON)
	    intersects.push_back(Intersection{-c / (2 * b), (Primitive*) this});
	return intersects;
    }

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

    intersect_caps(r, intersects);
    return intersects;
}

Tuple Cone::local_normal(const Tuple &t) const
{
    double distance = pow(t.get(0), 2) + pow(t.get(2), 2);
    if (m_closed &&
	distance + Constants::EPSILON < abs(m_minmax[1]) &&
	t.get(1) >= m_minmax[1] - Constants::EPSILON)
	return vector(0, 1, 0);
    else if (m_closed &&
	     distance + Constants::EPSILON < abs(m_minmax[0]) &&
	     t.get(1) <= m_minmax[0] + Constants::EPSILON)
	return vector(0, -1, 0);

    double y = sqrt(distance) * (t.get(1) > 0) ? -1 : 1;
    return vector(t.get(0), y, t.get(2));
}

// utility functions
BoundingBox Cone::local_bounds() const
{
    double a = abs(m_minmax[0]);
    double b = abs(m_minmax[1]);
    double limit = std::max(a, b);

    return BoundingBox{point(-limit, m_minmax[0], -limit), point(limit, m_minmax[1], limit)};
}