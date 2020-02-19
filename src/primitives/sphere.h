#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
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

    // line-sphere intersection
    std::vector<double> intersect(Ray &r) const;
};

#endif SPHERE_H