#include "geometry/primitives/plane.h"

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Plane::local_intersect(const core::Ray &ray) const
{
    std::vector<core::Intersection> intersects;

    if (std::abs(ray.direction()(1)) < constants::EPSILON)
	return intersects;

    intersects.push_back(core::Intersection{-ray.origin()(1) / ray.direction()(1), (Primitive*) this});
    return intersects;
}

math::Tuple4d geometry::primitive::Plane::local_normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    return math::vector(0, 1, 0);
}

// utility functions
core::BoundingBox geometry::primitive::Plane::local_bounds() const
{
    return core::BoundingBox{math::point(-INFINITY, 0, -INFINITY), math::point(INFINITY, 0, INFINITY)};
}
