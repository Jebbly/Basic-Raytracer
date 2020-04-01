#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <cmath>
#include <vector>
#include "utility/common.h"
#include "utility/helper.h"
#include "core/ray.h"
#include "math/tuple.h"
#include "math/matrix.h"

class BoundingBox
{
private:
    // attributes
    Tuple m_minmax[2];

public:
    BoundingBox(const Tuple &minimum = point(INFINITY, INFINITY, INFINITY), const Tuple &maximum = point(-INFINITY, -INFINITY, -INFINITY));

    // accessor methods
    const Tuple& get_minimum() const;
    const Tuple& get_maximum() const;

    void set_minimum(const Tuple &t);
    void set_maximum(const Tuple &t);

    // utility functions
    void add_point(const Tuple &point);
    bool contains_point(const Tuple &point) const;

    void add_bounds(const BoundingBox &box);
    bool contains_bounds(const BoundingBox &box) const;

    BoundingBox transform(const Matrix &transformation);

    bool intersect(const Ray &r) const;
};

#endif