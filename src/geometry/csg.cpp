#include "geometry/csg.h"

geometry::CSG::CSG(geometry::primitive::Primitive *left, geometry::primitive::Primitive *right, bool (*intersection_allowed)(bool, bool, bool)) :
    geometry::Group{},
    m_intersection_allowed{intersection_allowed}
{
    add_child(left);
    add_child(right);
}

// helper functions
std::vector<Intersection> geometry::CSG::filter_intersections(std::vector<Intersection> &xs) const
{
    bool left_hit, in_left = false, in_right = false;

    std::vector<Intersection> ret;
    for (int i = 0; i < xs.size(); i++)
    {
	left_hit = m_children.at(0)->includes(xs.at(i).get_object());
	if (m_intersection_allowed(left_hit, in_left, in_right))
	    ret.push_back(xs.at(i));

	if (left_hit)
	    in_left = !in_left;
	else
	    in_right = !in_right;
    }
    return ret;
}

// ray intersect functions
std::vector<Intersection> geometry::CSG::local_intersect(const Ray &r) const
{
    std::vector<Intersection> ret = Group::local_intersect(r);
    std::sort(ret.begin(), ret.end());
    return filter_intersections(ret);
}

// CSG boolean operations
bool geometry::csg_union(bool left_hit, bool in_left, bool in_right)
{
    return (left_hit && !in_right) || (!left_hit && !in_left);
}

bool geometry::csg_intersect(bool left_hit, bool in_left, bool in_right)
{
    return (left_hit && in_right) || (!left_hit && in_left);
}

bool geometry::csg_difference(bool left_hit, bool in_left, bool in_right)
{
    return (left_hit && !in_right) || (!left_hit && in_left);
}