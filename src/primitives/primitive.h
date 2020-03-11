#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "materials/material.h"

class Primitive
{
protected:
    // attributes
    Matrix m_transformation;
    Material* m_material;

    Primitive(const Matrix &transformation, Material *material);

public:
    // accessor methods
    const Matrix& get_transformation() const {return m_transformation;}
    const Material* get_material() const {return m_material;}

    void set_transform(const Matrix &m);
    void set_material(Material *m);

    // ray intersect functions
    Tuple color(const Tuple &point) const;

    virtual Tuple local_intersect(const Ray &r) const = 0;
    virtual Tuple local_normal(const Tuple &t) const = 0;
};

#endif