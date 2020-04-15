#include "geometry/group.h"

geometry::Group::Group(const math::Matrix4d &transformation, std::shared_ptr<material::Material> material) :
    Primitive{transformation, material},
    m_bounds{}
{}

// accessor methods
void geometry::Group::add_child(geometry::primitive::Primitive *object)
{
    object->parent = this;
    m_bounds.add_bounds(object->bounds());
    m_children.push_back(object);
}

void geometry::Group::transform(const math::Matrix4d &transformation)
{
    m_bounds = m_bounds.transform(transformation);
    Primitive::transform(transformation);
}

bool geometry::Group::includes(geometry::primitive::Primitive *object) const
{
    bool included = false;
    for (int i = 0; i < m_children.size(); i++)
    {
	if (m_children.at(i)->includes(object))
	    included = true;
    }
    return included;
}

// ray intersect functions
std::vector<core::Intersection> geometry::Group::local_intersect(const core::Ray &ray) const
{
    std::vector<core::Intersection> ret;
    if (m_bounds.intersect(ray))
    {
	for (int i = 0; i < m_children.size(); i++)
	{
	    std::vector<core::Intersection> object_intersects = m_children.at(i)->intersect(ray);
	    ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
	}
    }
    return ret;
}

math::Tuple4d geometry::Group::local_normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    assert(!"cannot find local_normal of Group");
    return math::vector(0, 0, 0);
}

// utility functions
core::BoundingBox geometry::Group::local_bounds() const
{
    return m_bounds;
}
