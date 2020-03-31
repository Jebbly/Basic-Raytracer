#ifndef GROUP_H
#define GROUP_H

#include <cassert>
#include <memory>
#include <vector>
#include "utility/common.h"
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
    Group(const Matrix &transformation = identity(), std::shared_ptr<Material> material = std::make_shared<ColorMaterial>(ColorMaterial{}));

    // copy overloads
    Group(const Group &g);
    Group& operator=(const Group &g);

    // accessor methods
    void add_child(Primitive *object);

    const std::vector<Primitive*>& get_children() const;

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;

    // utliity functions
    virtual void transform(const Matrix &transformation) override;
    virtual BoundingBox local_bounds() const override;
};

#endif