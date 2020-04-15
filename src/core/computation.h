#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <algorithm>
#include <vector>
#include "math/tuple.h"
#include "core/intersection.h"
#include "core/ray.h"
#include "geometry/primitives/primitive.h"

namespace core
{

class Computation
{
private:
    // attributes
    geometry::primitive::Primitive* m_object;
    math::Tuple4d m_point, m_eye, m_normal, m_reflect;
    math::Tuple4d m_over_point, m_under_point;
    double m_t;
    double m_n1, m_n2;

public:
    Computation(const Ray &ray, const Intersection &intersect, const std::vector<Intersection> &xs);

    // accessor methods
    inline geometry::primitive::Primitive* object() const {return m_object;}
    inline const math::Tuple4d& point() const {return m_point;}
    inline const math::Tuple4d& eye() const {return m_eye;}
    inline const math::Tuple4d& normal() const {return m_normal;}
    inline const math::Tuple4d& reflect() const {return m_reflect;}
    inline const math::Tuple4d& over_point() const {return m_over_point;}
    inline const math::Tuple4d& under_point() const {return m_under_point;}
    inline double t() const {return m_t;}
    inline double n1() const {return m_n1;}
    inline double n2() const {return m_n2;}
};

} // namespace core

#endif
