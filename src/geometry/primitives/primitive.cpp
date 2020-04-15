#include "geometry/primitives/primitive.h"

geometry::primitive::Primitive::Primitive(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material) :
    m_transformation{transformation},
    material{material},
    parent{nullptr}
{}

// helper functions
math::Tuple4d geometry::primitive::Primitive::world_to_object(math::Tuple4d point) const
{
    if (parent)
	point = ((Primitive*) parent)->world_to_object(point);

    return m_transformation.inverse() * point;
}

math::Tuple4d geometry::primitive::Primitive::normal_to_world(math::Tuple4d normal) const
{
    normal = m_transformation.inverse().transpose() * normal;
    normal(3) = 0;
    normal = normal.normalize();

    if (parent)
	normal = ((Primitive*) parent)->normal_to_world(normal);

    return normal;
}

// accessor method
void geometry::primitive::Primitive::transform(const math::Matrix4d &transformation)
{
    m_transformation = m_transformation * transformation;
}

bool geometry::primitive::Primitive::includes(Primitive *object) const
{
    return (this == object);
}

// ray intersect functions
math::Tuple4d geometry::primitive::Primitive::normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    math::Tuple4d object_point = m_transformation.inverse() * point;
    math::Tuple4d object_normal = local_normal(object_point, hit);
    math::Tuple4d world_normal = m_transformation.inverse().transpose() * object_normal;

    world_normal(3) = 0;
    return world_normal.normalize();
}

std::vector<core::Intersection> geometry::primitive::Primitive::intersect(const core::Ray &ray)
{
    core::Ray transformed_ray = ray.transform(m_transformation.inverse());
    return local_intersect(transformed_ray);
}

image::Color geometry::primitive::Primitive::color(const math::Tuple4d &point) const
{
    math::Tuple4d object_space = world_to_object(point);
    return material->color(object_space);
}

// utility functions
core::BoundingBox geometry::primitive::Primitive::bounds() const
{
    return local_bounds().transform(m_transformation);
}
