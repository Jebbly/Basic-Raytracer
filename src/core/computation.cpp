#include "core/computation.h"

Computation::Computation(const Ray &ray, const Intersection &intersect) :
    m_t{intersect.get_t()},
    m_object{intersect.get_object()},
    m_eye{-ray.get_direction()}
{
    m_point = ray.position(m_t);
    m_normal = normal(m_object, m_point);

    if (dot(m_normal, m_eye) < 0)
    {
	m_inside = true;
	m_normal = -m_normal;
    }
    else
	m_inside = false;

    m_over_point = m_point + m_normal * Constants::EPSILON;
}