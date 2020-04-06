#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <algorithm>
#include "math/tuple.h"
#include "core/computation.h"
#include "scene/light.h"

class SpotLight : public Light
{
private:
    // attributes
    math::Tuple4d m_position, m_direction;
    double m_outer_cutoff, m_inner_cutoff;

public:
    SpotLight(const math::Tuple3d &intensity, const math::Tuple4d &position, const math::Tuple4d &direction, double outer_cutoff, double inner_cutoff);

    // accessor methods
    const math::Tuple4d& get_position() const {return m_position;}
    double get_outer_cutoff() const {return m_outer_cutoff;}
    double get_inner_cutoff() const {return m_inner_cutoff;}
    virtual const math::Tuple4d get_direction(const math::Tuple4d &t) const override;

    // raytrace functions
    virtual const math::Tuple3d lighting(const Computation &comp) const override;
};

#endif