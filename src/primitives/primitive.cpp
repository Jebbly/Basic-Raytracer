#include "primitives/primitive.h"

Primitive::Primitive(const Matrix &transformation, const Material &material) :
    m_transformation{transformation},
    m_material{material}
{}

// accessor methods
void Primitive::set_transform(const Matrix &m)
{
    m_transformation = m;
}

void Primitive::set_material(const Material &m)
{
    m_material = m;
}

// ray intersect functions
std::vector<Intersection> Primitive::intersect(const Ray &r) const
{
    Ray transformed_ray = r.transform(m_transformation.inverse());
    Tuple t_values = local_intersect(transformed_ray);

    std::vector<Intersection> ret;
    for (int i = 0; i < t_values.get_size(); i++)
    {
	ret.push_back(Intersection{t_values.get(i), this});
    }
    return ret;
}

Tuple Primitive::normal(const Tuple &t) const
{
    Tuple object_point = multiply(m_transformation.inverse(), t);
    Tuple object_normal = local_normal(object_point);
    Tuple world_normal = multiply(m_transformation.inverse().transpose(), object_normal);

    world_normal.set(3, 0.0);
    return normalize(world_normal);
}