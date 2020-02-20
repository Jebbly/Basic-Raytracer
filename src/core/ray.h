#ifndef RAY_H
#define RAY_H

#include "math/tuple.h"

class Ray
{
private:
    // attributes
    Tuple m_origin, m_direction;

public:
    Ray(const Tuple &origin, const Tuple &direction);

    // accessor methods
    const Tuple& origin() const {return m_origin;}
    const Tuple& direction() const {return m_direction;}

    // ray operations
    Tuple position(double t) const;
};

#endif