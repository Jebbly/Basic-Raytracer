#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include <vector>
#include "math/matrix.h"
#include "math/tuple.h"
#include "core/bounding_box.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "material/color_material.h"
#include "material/material.h"

namespace core {class Intersection;}
namespace geometry {class Group;}

namespace geometry::primitive
{

class Primitive
{
protected:
    // attributes
    math::Matrix4d m_transformation;

    // helper functions
    math::Tuple4d world_to_object(math::Tuple4d point) const;
    math::Tuple4d normal_to_world(math::Tuple4d normal) const;

public:
    // attributes
    std::shared_ptr<material::Material> material;
    Group *parent;

    Primitive(const math::Matrix4d &transformation = math::identity(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));

    // accessor method
    virtual void transform(const math::Matrix4d &transformation);
    virtual bool includes(Primitive *object) const;

    // ray intersect functions
    math::Tuple4d normal(const math::Tuple4d &point, const core::Intersection &hit) const;
    std::vector<core::Intersection> intersect(const core::Ray &ray);
    image::Color color(const math::Tuple4d &point) const;

    virtual std::vector<core::Intersection> local_intersect(const core::Ray &ray) const = 0;
    virtual math::Tuple4d local_normal(const math::Tuple4d &point, const core::Intersection &hit) const = 0;

    // utility functions
    core::BoundingBox bounds() const;
    virtual core::BoundingBox local_bounds() const = 0;
};

} // namespace geometry::primitive

#endif
