#ifndef GROUP_H
#define GROUP_H

#include <cassert>
#include <memory>
#include <vector>
#include "math/matrix.h"
#include "math/tuple.h"
#include "core/bounding_box.h"
#include "core/intersection.h"
#include "geometry/primitives/primitive.h"
#include "material/material.h"

namespace geometry
{

class Group : public primitive::Primitive
{
protected:
    // attributes
    std::vector<Primitive*> m_children;
    core::BoundingBox m_bounds;

public:
    Group(const math::Matrix4d &transformation = math::identity(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));

    // accessor methods
    void add_child(primitive::Primitive *object);
    virtual void transform(const math::Matrix4d &transformation) override;
    virtual bool includes(primitive::Primitive *object) const override;

    // ray intersect functions
    virtual std::vector<core::Intersection> local_intersect(const core::Ray &ray) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &point, const core::Intersection &hit) const override;

    // utliity functions
    virtual core::BoundingBox local_bounds() const override;
};

} // namespace geometry

#endif
