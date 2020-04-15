#ifndef RAY_H
#define RAY_H

#include "math/matrix.h"
#include "math/tuple.h"

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
    inline const math::Tuple4d& origin() const {return m_origin;}
    inline const math::Tuple4d& direction() const {return m_direction;}

    // ray operations
    math::Tuple4d position(double t) const;
    Ray transform(const math::Matrix4d &transformation) const;
};

} // namespace core

#endif
