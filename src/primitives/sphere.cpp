#include "primitives/sphere.h"

// primitive-specific ray intersect functions
Tuple Sphere::local_intersect(const Ray &r) const
{
    Tuple sphere_to_ray = r.get_origin() - point(0, 0, 0);
    double a = dot(r.get_direction(), r.get_direction());
    double b = 2 * dot(r.get_direction(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1;
    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
	return Tuple{0};

    Tuple intersects{2};
    intersects.set(0, (-b + sqrt(discriminant)) / (2 * a));
    intersects.set(1, (-b - sqrt(discriminant)) / (2 * a));
    return intersects;
}

Tuple Sphere::local_normal(const Tuple &t) const
{
    return normalize(t - point(0.0, 0.0, 0.0));
}