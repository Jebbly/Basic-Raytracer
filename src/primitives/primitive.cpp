#include "primitives/primitive.h"

Primitive::Primitive(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material) :
    m_transformation{transformation},
    m_material{material},
    m_parent{nullptr}
{}

// helper functions
math::Tuple4d Primitive::world_to_object(math::Tuple4d point) const
{
    if (m_parent)
	point = ((Primitive*) m_parent)->world_to_object(point);

    return m_transformation.inverse() * point;
}

math::Tuple4d Primitive::normal_to_world(math::Tuple4d normal) const
{
    normal = m_transformation.inverse().transpose() * normal;
    normal(3) = 0;
    normal = normal.normalize();

    if (m_parent)
	normal = ((Primitive*) m_parent)->normal_to_world(normal);

    return normal;
}

// accessor methods
const math::Matrix4d& Primitive::get_transformation() const
{
    return m_transformation;
}

std::shared_ptr<material::Material> Primitive::get_material()
{
    return m_material;
}

const Group* Primitive::get_parent() const
{
    return m_parent;
}

void Primitive::set_transform(const math::Matrix4d &m)
{
    m_transformation = m;
}

void Primitive::set_material(std::shared_ptr<material::Material> m)
{
    m_material = m;
}

void Primitive::set_parent(Group *p)
{
    m_parent = p;
}

bool Primitive::includes(Primitive *p) const
{
    return (this == p);
}

// ray intersect functions
math::Tuple4d Primitive::normal(const math::Tuple4d &t, const Intersection &hit) const
{
    math::Tuple4d object_point = m_transformation.inverse() * t;
    math::Tuple4d object_normal = local_normal(object_point, hit);
    math::Tuple4d world_normal = m_transformation.inverse().transpose() * object_normal;

    world_normal(3) = 0;
    return world_normal.normalize();
}

std::vector<Intersection> Primitive::intersect(const Ray &r)
{
    Ray transformed_ray = r.transform(m_transformation.inverse());
    return local_intersect(transformed_ray);
}

math::Tuple3d Primitive::color(const math::Tuple4d &point) const
{
    math::Tuple4d object_space = world_to_object(point);
    return m_material->get_color(object_space);
}

// utility functions
void Primitive::transform(const math::Matrix4d &transformation)
{
    m_transformation = m_transformation * transformation;
}

BoundingBox Primitive::bounds() const
{
    return local_bounds().transform(m_transformation);
}