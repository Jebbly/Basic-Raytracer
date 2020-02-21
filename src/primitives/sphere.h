#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"

class Sphere
{
private:
    // attributes
    int m_id;
    Matrix m_transformation;

public:
    Sphere();

    // accessor methods
    int id() const {return m_id;}
    const Matrix& transformation() const {return m_transformation;}

    void set_transform(const Matrix &m);

    // line-sphere intersection
    Tuple intersect(const Ray &r) const;
};

#endif