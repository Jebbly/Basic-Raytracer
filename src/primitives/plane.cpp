#include "primitives/plane.h"

// ray intersect functions
std::vector<Intersection> Plane::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    if (abs(r.get_direction().get(1)) < Constants::EPSILON)
	return intersects;

    intersects.push_back(Intersection{-r.get_origin().get(1) / r.get_direction().get(1), (Primitive*) this});
    return intersects;
}

Tuple Plane::local_normal(const Tuple &t) const
{
    return vector(0, 1, 0);
}

// utility functions
BoundingBox Plane::local_bounds() const
{
    return BoundingBox{point(-INFINITY, 0, -INFINITY), point(INFINITY, 0, INFINITY)};
}