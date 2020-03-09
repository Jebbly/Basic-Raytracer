#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "math/tuple.h"
#include "core/computation.h"
#include "scene/light.h"

class PointLight : public Light
{
private:
    // attributes
    Tuple m_position;

public:
    PointLight(const Tuple &intensity, const Tuple &position);

    // accessor methods
    const Tuple& get_position() const {return m_position;}
    virtual const Tuple get_direction(const Tuple &t) const override;
    
    // raytrace functions
    virtual const Tuple lighting(const Computation &comp) const override;
};

#endif