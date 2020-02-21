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

Ray Ray::transform(const Matrix &transformation) const
{
    return Ray{multiply(transformation, m_origin), multiply(transformation, m_direction)};
}