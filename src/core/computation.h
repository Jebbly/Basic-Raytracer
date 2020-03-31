#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <vector>
#include <algorithm>
#include "math/tuple.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "primitives/primitive.h"

class Computation
{
private:
    // attributes
    Primitive* m_object;
    Tuple m_point, m_eye, m_normal, m_reflect;
    Tuple m_over_point, m_under_point;
    double m_t;
    double m_n1, m_n2;
    bool m_inside;

public:
    Computation(const Ray &ray, const Intersection &intersect, const std::vector<Intersection> &xs);
    
    // accessor methods
    Primitive* get_object() const {return m_object;}
    const Tuple& get_point() const {return m_point;}
    const Tuple& get_eye() const {return m_eye;}
    const Tuple& get_normal() const {return m_normal;}
    const Tuple& get_reflect() const {return m_reflect;}
    const Tuple& get_over_point() const {return m_over_point;}
    const Tuple& get_under_point() const {return m_under_point;}
    double get_t() const {return m_t;}
    double get_n1() const {return m_n1;}
    double get_n2() const {return m_n2;}
    bool get_inside() const {return m_inside;}
};

#endif