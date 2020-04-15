#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <array>
#include <cmath>
#include <vector>
#include "utility/constants.h"
#include "utility/helper.h"
#include "math/matrix.h"
#include "math/tuple.h"
#include "core/ray.h"

namespace core
{

class BoundingBox
{
private:
    // attributes
    math::Tuple4d m_minmax[2];

public:
    BoundingBox(const math::Tuple4d &minimum = math::point(INFINITY, INFINITY, INFINITY), const math::Tuple4d &maximum = math::point(-INFINITY, -INFINITY, -INFINITY));

    // accessor methods
    inline const math::Tuple4d& minimum() const {return m_minmax[0];}
    inline const math::Tuple4d& maximum() const {return m_minmax[1];}

    // utility functions
    void add_point(const math::Tuple4d &point);
    bool contains_point(const math::Tuple4d &point) const;

    void add_bounds(const BoundingBox &box);
    bool contains_bounds(const BoundingBox &box) const;

    BoundingBox transform(const math::Matrix4d &transformation);

    bool intersect(const Ray &ray) const;
};

} // namespace core

#endif
