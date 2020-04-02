#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cassert>
#include <cmath>
#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "materials/color_material.h"
#include "primitives/primitive.h"

class Triangle : public Primitive
{
protected:
    // triangle attributes
    math::Tuple4d m_points[3];
    math::Tuple4d m_edges[2];
  
private:
    // flat shading attribute
    math::Tuple4d m_normal;

public:
    Triangle(const math::Tuple4d &point1, const math::Tuple4d &point2, const math::Tuple4d &point3);

    // accessor methods
    const math::Tuple4d& get_point(int index) const;
    const math::Tuple4d& get_edge(int index) const;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif