#include "primitives/plane.h"

// ray intersect functions
Tuple Plane::local_intersect(const Ray &r) const
{
    if (abs(r.get_direction().get(1)) < Constants::EPSILON)
	return Tuple{0};

    Tuple intersects{1};
    intersects.set(0, -r.get_origin().get(1) / r.get_direction().get(1));
    return intersects;
}

Tuple Plane::local_normal(const Tuple &t) const
{
    return vector(0, 1, 0);
}