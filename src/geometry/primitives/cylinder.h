#ifndef CYLINDER_H
#define CYLINDER_H

#include <array>
#include <cmath>
#include <memory>
#include <utility>
#include <vector>
#include "utility/constants.h"
#include "utility/helper.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "material/material.h"
#include "material/color_material.h"
#include "geometry/primitives/primitive.h"

namespace geometry::primitive
{

class Cylinder : public Primitive
{
private:
    // attributes
    double m_minmax[2];
    bool m_closed;

public:
    Cylinder(const math::Matrix4d &transformation = math::identity(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}), double minimum = -INFINITY, double maximum = INFINITY, bool closed = false);

    // ray intersect functions
    virtual std::vector<core::Intersection> local_intersect(const core::Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const core::Intersection &hit) const override;

    // utility functions
    virtual core::BoundingBox local_bounds() const override;
};

} // namespace geometry::primitive

#endif