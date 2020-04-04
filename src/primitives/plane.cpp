#include "primitives/plane.h"

// ray intersect functions
std::vector<Intersection> Plane::local_intersect(const Ray &r) const
{
    std::vector<Intersection> intersects;

    if (abs(r.get_direction()(1)) < constants::EPSILON)
	return intersects;

    intersects.push_back(Intersection{-r.get_origin()(1) / r.get_direction()(1), (Primitive*) this});
    return intersects;
}

math::Tuple4d Plane::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    return math::vector<double>(0, 1, 0);
}

// utility functions
BoundingBox Plane::local_bounds() const
{
    return BoundingBox{math::point<double>(-INFINITY, 0, -INFINITY), math::point<double>(INFINITY, 0, INFINITY)};
}