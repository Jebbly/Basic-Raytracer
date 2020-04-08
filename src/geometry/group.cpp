#include "geometry/group.h"

geometry::Group::Group(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material) :
    Primitive{transformation, material},
    m_bounds{}
{}

// accessor methods
void geometry::Group::add_child(geometry::primitive::Primitive *object)
{
    object->set_parent(this);
    m_bounds.add_bounds(object->bounds());
    m_children.push_back(object);
}

const std::vector<geometry::primitive::Primitive*>& geometry::Group::get_children() const
{
    return m_children;
}

bool geometry::Group::includes(geometry::primitive::Primitive *p) const
{
    bool included = false;
    for (int i = 0; i < m_children.size(); i++)
    {
	if (m_children.at(i)->includes(p))
	    included = true;
    }
    return included;
}

// ray intersect functions
std::vector<Intersection> geometry::Group::local_intersect(const Ray &r) const
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

math::Tuple4d geometry::Group::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    assert(!"cannot find local_normal of Group");
    return math::vector<double>(0, 0, 0);
}

// utility functions
void geometry::Group::transform(const math::Matrix4d &transformation)
{
    m_bounds = m_bounds.transform(transformation);
    Primitive::transform(transformation);
}

BoundingBox geometry::Group::local_bounds() const
{
    return m_bounds;
}