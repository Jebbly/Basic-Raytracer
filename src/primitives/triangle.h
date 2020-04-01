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
    Tuple m_points[3];
    Tuple m_edges[2];
  
private:
    // flat shading attribute
    Tuple m_normal;

public:
    Triangle(const Tuple &point1, const Tuple &point2, const Tuple &point3);

    // accessor methods
    const Tuple& get_point(int index) const;
    const Tuple& get_edge(int index) const;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif