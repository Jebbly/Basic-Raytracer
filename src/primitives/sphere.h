#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/material.h"

class Sphere
{
private:
    // attributes
    int m_id;
    Matrix m_transformation;
    Material m_material;

public:
    Sphere();

    // accessor methods
    int id() const {return m_id;}
    const Matrix& get_transformation() const {return m_transformation;}
    const Material& get_material() const {return m_material;}

    void set_transform(const Matrix &m);
    void set_material(const Material &m);

    // ray intersect functions
    Tuple intersect(const Ray &r) const;
    Tuple normal(const Tuple &t) const;
};

#endif