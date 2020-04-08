#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <vector>
#include <algorithm>
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
    bool m_inside;

public:
    Computation(const Ray &ray, const Intersection &intersect, const std::vector<Intersection> &xs);

    // accessor methods
    geometry::primitive::Primitive* get_object() const { return m_object; }
    const math::Tuple4d& get_point() const { return m_point; }
    const math::Tuple4d& get_eye() const { return m_eye; }
    const math::Tuple4d& get_normal() const { return m_normal; }
    const math::Tuple4d& get_reflect() const { return m_reflect; }
    const math::Tuple4d& get_over_point() const { return m_over_point; }
    const math::Tuple4d& get_under_point() const { return m_under_point; }
    double get_t() const { return m_t; }
    double get_n1() const { return m_n1; }
    double get_n2() const { return m_n2; }
    bool get_inside() const { return m_inside; }
};

} // namespace core

#endif