#ifndef RAY_H
#define RAY_H

#include "math/tuple.h"
#include "math/matrix.h"

namespace core
{

class Ray
{
private:
    // attributes
    math::Tuple4d m_origin, m_direction;

public:
    Ray(const math::Tuple4d &origin, const math::Tuple4d &direction);

    // accessor methods
    const math::Tuple4d& get_origin() const { return m_origin; }
    const math::Tuple4d& get_direction() const { return m_direction; }

    // ray operations
    math::Tuple4d position(double t) const;
    Ray transform(const math::Matrix4d &m) const;
};

} // namespace core

#endif