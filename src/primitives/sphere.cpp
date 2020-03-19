#include "primitives/sphere.h"

// primitive-specific ray intersect functions
std::vector<Intersection> Sphere::local_intersect(const Ray &r) const
{
    Tuple sphere_to_ray = r.get_origin() - point(0, 0, 0);
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

Tuple Sphere::local_normal(const Tuple &t) const
{
    return normalize(t - point(0.0, 0.0, 0.0));
}