#ifndef GROUP_H
#define GROUP_H

#include <cassert>
#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "materials/material.h"
#include "primitives/primitive.h"

class Group : public Primitive
{
private:
    // attributes
    std::vector<Primitive*> m_children;

public:
    Group(const Matrix &transformation = identity());

    // accessor methods
    void add_child(Primitive *object);

    // ray intersect functions
    virtual std::vector<Intersection> local_intersect(const Ray &r) const override;
    virtual Tuple local_normal(const Tuple &t) const override;
};

#endif