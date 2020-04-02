#ifndef CONE_H
#define CONE_H

#include <cmath>
#include <memory>
#include <vector>
#include "utility/common.h"
#include "utility/helper.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "materials/color_material.h"
#include "primitives/primitive.h"

class Cone : public Primitive
{
private:
    // attributes
    double m_minmax[2];
    bool m_closed;

public:
    Cone(const math::Matrix4d &transformation = math::identity<double, 4>(), std::shared_ptr<Material> material = std::make_shared<ColorMaterial>(ColorMaterial{}), double minimum = -INFINITY, double maximum = INFINITY, bool closed = false);

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;

    // utility functions
    virtual BoundingBox local_bounds() const override;
};

#endif