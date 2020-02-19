#include "primitives/sphere.h"

// line-sphere intersection
std::vector<double> Sphere::intersect(Ray &r) const
{
    std::vector<double> intersections;

    Tuple sphere_to_ray = r.origin() - point(0, 0, 0);
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1;
    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
	return intersections;

    for (int i = -1; i <= 1; i += 2)
    {
	double t = (-b + i * sqrt(discriminant)) / (2 * a);
	intersections.push_back(t);
    }

    return intersections;
}