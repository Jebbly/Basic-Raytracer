#ifndef LIGHTING_H
#define LIGHTING_H

#include <cmath>
#include "math/tuple.h"
#include "core/material.h"

class Light
{
protected:
    // attributes
    Tuple m_intensity;

    Light(const Tuple &intensity);

public:
    // accessor methods
    const Tuple& get_intensity() const {return m_intensity;}
    virtual const Tuple get_direction(const Tuple &t) const = 0;

    // raytrace functions
    virtual const Tuple lighting(const Material &mat, const Tuple &position, const Tuple &eye, const Tuple &normal, bool shadowed) const = 0;
};

#endif