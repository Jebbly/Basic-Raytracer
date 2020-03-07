#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/material.h"

class Primitive
{
protected:
    // attributes
    Matrix m_transformation;
    Material m_material;

    Primitive(const Matrix &transformation = identity(), const Material &material = Material{});

public:
    // accessor methods
    const Matrix& get_transformation() const {return m_transformation;}
    const Material& get_material() const {return m_material;}

    void set_transform(const Matrix &m);
    void set_material(const Material &m);

    // ray intersect functions
    virtual Tuple intersect(const Ray &r) const = 0;
    virtual Tuple normal(const Tuple &t) const = 0;
};

#endif