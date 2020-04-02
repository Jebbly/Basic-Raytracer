#include "core/ray.h"

Ray::Ray(const math::Tuple4d &origin, const math::Tuple4d &direction) :
    m_origin{origin},
    m_direction{direction}
{};

// ray operations
math::Tuple4d Ray::position(double t) const
{
    return m_origin + m_direction * t;
}

Ray Ray::transform(const math::Matrix4d &transformation) const
{
    return Ray{transformation * m_origin, transformation * m_direction};
}