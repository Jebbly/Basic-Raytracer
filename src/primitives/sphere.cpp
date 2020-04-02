#include "primitives/sphere.h"

// ray intersect functions
std::vector<Intersection> Sphere::local_intersect(const Ray &r) const
{
    math::Tuple4d sphere_to_ray = r.get_origin() - math::point<double>(0, 0, 0);
    double a = dot(r.get_direction(), r.get_direction());
    double b = 2 * dot(r.get_direction(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1;
    double discriminant = pow(b, 2) - 4 * a * c;

    std::vector<Intersection> intersects;
    if (discriminant >= 0)
    {
	intersects.push_back(Intersection{(-b + sqrt(discriminant)) / (2 * a), (Primitive*) this});
	intersects.push_back(Intersection{(-b - sqrt(discriminant)) / (2 * a), (Primitive*) this});
    }
    return intersects;
}

math::Tuple4d Sphere::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    return (t - math::point<double>(0, 0, 0));
}

// utility functions
BoundingBox Sphere::local_bounds() const
{
    return BoundingBox{math::point<double>(-1, -1, -1), math::point<double>(1, 1, 1)};
}