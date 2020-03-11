#ifndef RING_MATERIAL_H
#define RING_MATERIAL_H

#include <cmath>
#include "math/tuple.h"
#include "materials/material.h"
#include "materials/pattern.h"

class RingMaterial : public Pattern
{
public:
    RingMaterial(const Tuple &color_a = color(0, 0, 0), const Tuple &color_b = color(1, 1, 1), const Matrix &transformation = identity(), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200);

    // raytrace functions
    virtual Tuple get_pattern(const Tuple &pos) const override;
};

#endif