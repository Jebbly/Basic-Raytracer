#ifndef SPHERE_H
#define SPHERE_H

#include "main/common.h"
#include "math/tuple.h"
#include "core/ray.h"

class Sphere
{
private:
    // attributes
    int m_id;

public:
    Sphere();

    // accessor methods
    int id() const {return m_id;}

    // line-sphere intersection
    Tuple intersect(const Ray &r) const;
};

#endif