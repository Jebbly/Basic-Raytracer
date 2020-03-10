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