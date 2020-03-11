#include "primitives/primitive.h"

Primitive::Primitive(const Matrix &transformation, Material *material) :
    m_transformation{transformation},
    m_material{material}
{}

// accessor methods
void Primitive::set_transform(const Matrix &m)
{
    m_transformation = m;
}

void Primitive::set_material(Material *m)
{
    m_material = m;
}

// ray intersect functions
Tuple Primitive::color(const Tuple &point) const
{
    Tuple object_space = multiply(m_transformation.inverse(), point);
    return m_material->get_color(object_space);
}