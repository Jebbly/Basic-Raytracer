#ifndef LIGHTING_H
#define LIGHTING_H

#include <cmath>
#include "math/tuple.h"
#include "core/computation.h"
#include "materials/material.h"

class Light
{
protected:
    // attributes
    Tuple m_intensity;

    Light(const Tuple &intensity);
    
    // phong shading
    const Tuple phong_shading(const Primitive *object, const Tuple &position, const Tuple &eye, const Tuple &normal) const;

public:
    // accessor methods
    const Tuple& get_intensity() const {return m_intensity;}
    virtual const Tuple get_direction(const Tuple &t) const = 0;

    // raytrace functions
    virtual const Tuple lighting(const Computation &comp) const = 0;
};

#endif