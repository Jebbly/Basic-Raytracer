#include "primitives/group.h"

Group::Group(const Matrix &transformation, std::shared_ptr<Material> material) :
    Primitive{transformation, material},
    m_bounds{}
{}

// copy overloads
Group::Group(const Group &g) :
    m_children{g.m_children},
    m_bounds{g.m_bounds}
{
    for (int i = 0; i < m_children.size(); i++)
    {
	m_children.at(i)->set_parent(this);
    }
}

Group& Group::operator=(const Group &g)
{
    if (&g == this)
	return *this;

    m_children = g.m_children;
    m_bounds = g.m_bounds;
    
    for (int i = 0; i < m_children.size(); i++)
    {
	m_children.at(i)->set_parent(this);
    }

    return *this;
}

// accessor methods
void Group::add_child(Primitive *object)
{
    object->set_parent(this);
    m_bounds.add_bounds(object->bounds());
    m_children.push_back(object);
}

const std::vector<Primitive*>& Group::get_children() const
{
    return m_children;
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
void Group::transform(const Matrix &transformation)
{
    m_bounds = m_bounds.transform(transformation);
    Primitive::transform(transformation);
}

BoundingBox Group::local_bounds() const
{
    return m_bounds;
}