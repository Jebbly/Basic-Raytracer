#ifndef CSG_H
#define CSG_H

#include <vector>
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/intersection.h"
#include "geometry/group.h"
#include "geometry/primitives/primitive.h"
#include "material/material.h"

namespace geometry
{

class CSG : public Group
{
private:
    // attributes
    bool (*m_intersection_allowed)(bool, bool, bool);

    // helper functions
    using Group::add_child;
    std::vector<core::Intersection> filter_intersections(std::vector<core::Intersection> &xs) const;

public:
    CSG(primitive::Primitive *left, primitive::Primitive *right, bool (*intersection_allowed)(bool, bool, bool));

    // ray intersect functions
    virtual std::vector<core::Intersection> local_intersect(const core::Ray &ray) const override;
};

// CSG boolean operations
bool csg_union(bool left_hit, bool in_left, bool in_right);
bool csg_intersect(bool left_hit, bool in_left, bool in_right);
bool csg_difference(bool left_hit, bool in_left, bool in_right);

} // namespace geometry

#endif
