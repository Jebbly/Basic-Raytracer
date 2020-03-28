#include "primitives/primitive.h"

Primitive::Primitive(const Matrix &transformation, Material *material) :
    m_transformation{transformation},
    m_material{material},
    m_parent{nullptr}
{}

// helper functions
Tuple Primitive::world_to_object(Tuple point) const
{
    if (m_parent)
	point = ((Primitive*) m_parent)->world_to_object(point);

    return multiply(m_transformation.inverse(), point);
}

Tuple Primitive::normal_to_world(Tuple normal) const
{
    normal = multiply(m_transformation.inverse().transpose(), normal);
    normal.set(3, 0);
    normal = normalize(normal);

    if (m_parent)
	normal = ((Primitive*) m_parent)->normal_to_world(normal);

    return normal;
}

// accessor methods
const Matrix& Primitive::get_transformation() const
{
    return m_transformation;
}

const Material* Primitive::get_material() const
{
    return m_material;
}

const Group* Primitive::get_parent() const
{
    return m_parent;
}

void Primitive::set_transform(const Matrix &m)
{
    m_transformation = m;
}

void Primitive::set_material(Material *m)
{
    m_material = m;
}

void Primitive::set_parent(Group *p)
{
    m_parent = p;
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
    Tuple object_space = world_to_object(point);
    return m_material->get_color(object_space);
}

// utility functions
void Primitive::transform(const Matrix &transformation)
{
    m_transformation = multiply(m_transformation, transformation);
}

BoundingBox Primitive::bounds() const
{
    return local_bounds().transform(m_transformation);
}