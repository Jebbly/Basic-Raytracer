#include "core/ray.h"

Ray::Ray(const Tuple &origin, const Tuple &direction) :
    m_origin{origin},
    m_direction{direction}
{};

// ray operations
Tuple Ray::position(double t) const
{
    return m_origin + m_direction * t;
}