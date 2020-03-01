#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "math/tuple.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "primitives/sphere.h"

class Computation
{
private:
    // attributes
    Sphere m_object;
    Tuple m_point, m_eye, m_normal;
    double m_t;
    bool m_inside;

public:
    Computation(const Ray &ray, const Intersection &intersect);
    
    // accessor methods
    const Sphere& get_object() const {return m_object;}
    const Tuple& get_point() const {return m_point;}
    const Tuple& get_eye() const {return m_eye;}
    const Tuple& get_normal() const {return m_normal;}
    double get_t() const {return m_t;}
    bool get_inside() const {return m_inside;}
};

#endif