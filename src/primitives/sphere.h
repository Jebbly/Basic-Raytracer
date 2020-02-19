#ifndef SPHERE_H
#define SPHERE_H

#include "main/common.h"
#include "core/ray.h"

class Sphere
{
private:
    // attributes
    int m_id;

public:
    Sphere()
    {
	static int id = 0;
	m_id = ++id;
    }

    // accessor methods
    int id() const {return m_id;}

    // line-sphere intersection
    Tuple intersect(const Ray &r) const;
};

#endif SPHERE_H