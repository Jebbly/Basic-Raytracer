#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <cmath>
#include <vector>
#include "utility/constants.h"
#include "utility/helper.h"
#include "core/ray.h"
#include "math/tuple.h"
#include "math/matrix.h"

namespace core
{

class BoundingBox
{
private:
    // attributes
    math::Tuple4d m_minmax[2];

public:
    BoundingBox(const math::Tuple4d &minimum = math::point<double>(INFINITY, INFINITY, INFINITY), const math::Tuple4d &maximum = math::point<double>(-INFINITY, -INFINITY, -INFINITY));

    // accessor methods
    const math::Tuple4d& get_minimum() const;
    const math::Tuple4d& get_maximum() const;

    void set_minimum(const math::Tuple4d &t);
    void set_maximum(const math::Tuple4d &t);

    // utility functions
    void add_point(const math::Tuple4d &point);
    bool contains_point(const math::Tuple4d &point) const;

    void add_bounds(const BoundingBox &box);
    bool contains_bounds(const BoundingBox &box) const;

    BoundingBox transform(const math::Matrix4d &transformation);

    bool intersect(const Ray &r) const;
};

} // namespace core

#endif