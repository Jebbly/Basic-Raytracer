#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "math/tuple.h"
#include "core/computation.h"
#include "scene/light.h"

class PointLight : public Light
{
private:
    // attributes
    math::Tuple4d m_position;

public:
    PointLight(const math::Tuple3d &intensity, const math::Tuple4d &position);

    // accessor methods
    const math::Tuple4d& get_position() const {return m_position;}
    virtual const math::Tuple4d get_direction(const math::Tuple4d &t) const override;
    
    // raytrace functions
    virtual const math::Tuple3d lighting(const Computation &comp) const override;
};

#endif