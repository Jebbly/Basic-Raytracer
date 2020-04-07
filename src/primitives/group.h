#ifndef GROUP_H
#define GROUP_H

#include <cassert>
#include <memory>
#include <vector>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Group : public Primitive
{
protected:
    // attributes
    std::vector<Primitive*> m_children;
    BoundingBox m_bounds;

public:
    Group(const math::Matrix4d &transformation = math::identity<double, 4>(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));

    // accessor methods
    void add_child(Primitive *object);

    const std::vector<Primitive*>& get_children() const;
    virtual bool includes(Primitive *p) const override;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const Intersection &hit) const override;

    // utliity functions
    virtual void transform(const math::Matrix4d &transformation) override;
    virtual BoundingBox local_bounds() const override;
};

#endif