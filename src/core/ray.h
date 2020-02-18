#ifndef RAY_H
#define RAY_H

#include "math/tuple.h"

class Ray
{
private:
    Tuple m_origin, m_direction;

public:
    Ray(Tuple &origin, Tuple &direction) :
	m_origin{std::move(origin)},
	m_direction{std::move(direction)}
    {};

    // ray operations
    Tuple position(double t) const;
};

#endif