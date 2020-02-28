#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "math/tuple.h"

class PointLight
{
private:
    // attributes
    Tuple m_intensity;
    Tuple m_position;

public:
    PointLight(const Tuple &intensity, const Tuple &position);
};

#endif