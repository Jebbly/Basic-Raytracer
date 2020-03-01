#include "primitives/sphere.h"

Sphere::Sphere(const Matrix &transformation, const Material &material) :
    m_transformation{transformation},
    m_material{material}
{
    static int id = 0;
    m_id = ++id;
}

// accessor methods
void Sphere::set_transform(const Matrix &m)
{
    m_transformation = m;
}

void Sphere::set_material(const Material &m)
{
    m_material = m;
}

// ray intersect functions
Tuple Sphere::intersect(const Ray &r) const
{
    Ray transformed_ray = r.transform(m_transformation.inverse());
    Tuple sphere_to_ray = transformed_ray.get_origin() - point(0, 0, 0);
    double a = dot(transformed_ray.get_direction(), transformed_ray.get_direction());
    double b = 2 * dot(transformed_ray.get_direction(), sphere_to_ray);
    double c = dot(sphere_to_ray, sphere_to_ray) - 1;
    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
	return Tuple{0};

    Tuple intersects{2};
    intersects.set(0, (-b + sqrt(discriminant)) / (2 * a));
    intersects.set(1, (-b - sqrt(discriminant)) / (2 * a));
    return intersects;
}

Tuple Sphere::normal(const Tuple &t) const
{
    Tuple object_point = multiply(m_transformation.inverse(), t);
    Tuple object_normal = normalize(object_point - point(0.0, 0.0, 0.0));
    Tuple world_normal = multiply(m_transformation.inverse().transpose(), object_normal);

    world_normal.set(3, 0.0);
    return normalize(world_normal);
}