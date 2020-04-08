#ifndef CSG_H
#define CSG_H

#include <memory>
#include <vector>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "geometry/primitives/primitive.h"
#include "geometry/group.h"

namespace geometry
{

class CSG : public Group
{
private:
    // attributes
    bool (*m_intersection_allowed)(bool, bool, bool);

    // helper functions
    using Group::add_child;
    std::vector<Intersection> filter_intersections(std::vector<Intersection> &xs) const;

public:
    CSG(primitive::Primitive *left, primitive::Primitive *right, bool (*intersection_allowed)(bool, bool, bool));

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
};

// CSG boolean operations
bool csg_union(bool left_hit, bool in_left, bool in_right);
bool csg_intersect(bool left_hit, bool in_left, bool in_right);
bool csg_difference(bool left_hit, bool in_left, bool in_right);

} // namespace geometry

#endif