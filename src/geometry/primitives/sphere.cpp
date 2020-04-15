#include "geometry/primitives/sphere.h"

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Sphere::local_intersect(const core::Ray &r) const
{
    math::Tuple4d sphere_to_ray = r.get_origin() - math::point(0, 0, 0);
    double a = dot(r.get_direction(), r.get_direction());
    double b = 2 * dot(r.get_direction(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1;
    double discriminant = pow(b, 2) - 4 * a * c;

    std::vector<core::Intersection> intersects;
    if (discriminant >= 0)
    {
	intersects.push_back(core::Intersection{(-b + sqrt(discriminant)) / (2 * a), (Primitive*) this});
	intersects.push_back(core::Intersection{(-b - sqrt(discriminant)) / (2 * a), (Primitive*) this});
    }
    return intersects;
}

math::Tuple4d geometry::primitive::Sphere::local_normal(const math::Tuple4d &t, const core::Intersection &hit) const
{
    return (t - math::point(0, 0, 0));
}

// utility functions
core::BoundingBox geometry::primitive::Sphere::local_bounds() const
{
    return core::BoundingBox{math::point(-1, -1, -1), math::point(1, 1, 1)};
}