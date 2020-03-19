#include "primitives/plane.h"

// ray intersect functions
std::vector<double> Plane::local_intersect(const Ray &r) const
{
    std::vector<double> intersects;

    if (abs(r.get_direction().get(1)) < Constants::EPSILON)
	return intersects;

    intersects.push_back(-r.get_origin().get(1) / r.get_direction().get(1));
    return intersects;
}

Tuple Plane::local_normal(const Tuple &t) const
{
    return vector(0, 1, 0);
}