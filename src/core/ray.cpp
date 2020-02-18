#include "core/ray.h"

Tuple Ray::position(double t) const
{
    return m_origin + m_direction * t;
}