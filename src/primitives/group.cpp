#include "primitives/group.h"

Group::Group(const Matrix &transformation, Material *material) :
    Primitive{transformation, material},
    m_bounds{}
{}

// accessor methods
void Group::add_child(Primitive *object)
{
    object->set_parent(this);
    m_bounds.add_bounds(object->bounds());
    m_children.push_back(object);
}

// ray intersect functions
std::vector<Intersection> Group::local_intersect(const Ray &r) const
{
    std::vector<Intersection> ret;
    if (m_bounds.intersect(r))
    {
	for (int i = 0; i < m_children.size(); i++)
	{
	    std::vector<Intersection> object_intersects = m_children.at(i)->intersect(r);
	    ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
	}
    }
    return ret;
}

Tuple Group::local_normal(const Tuple &t) const
{
    assert(!"cannot find local_normal of Group");
    return vector(0, 0, 0);
}

// utility functions
BoundingBox Group::local_bounds() const
{
    return m_bounds;
}