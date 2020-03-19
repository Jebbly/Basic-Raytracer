#include "primitives/primitive.h"

Primitive::Primitive(const Matrix &transformation, Material *material) :
    m_transformation{transformation},
    m_material{material}
{}

// accessor methods
const Matrix& Primitive::get_transformation() const
{
    return m_transformation;
}

const Material* Primitive::get_material() const
{
    return m_material;
}

void Primitive::set_transform(const Matrix &m)
{
    m_transformation = m;
}

void Primitive::set_material(Material *m)
{
    m_material = m;
}

// ray intersect functions
Tuple Primitive::normal(const Tuple &t) const
{
    Tuple object_point = multiply(m_transformation.inverse(), t);
    Tuple object_normal = local_normal(object_point);
    Tuple world_normal = multiply(m_transformation.inverse().transpose(), object_normal);

    world_normal.set(3, 0.0);
    return normalize(world_normal);
}

std::vector<Intersection> Primitive::intersect(const Ray &r)
{
    Ray transformed_ray = r.transform(m_transformation.inverse());
    return local_intersect(transformed_ray);
}

Tuple Primitive::color(const Tuple &point) const
{
    Tuple object_space = multiply(m_transformation.inverse(), point);
    return m_material->get_color(object_space);
}