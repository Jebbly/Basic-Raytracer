#ifndef STRIPE_MATERIAL_H
#define STRIPE_MATERIAL_H

#include "math/tuple.h"
#include "materials/material.h"
#include "materials/pattern.h"

class StripeMaterial : public Pattern
{
public:
    StripeMaterial(const Tuple &color_a = color(0, 0, 0), const Tuple &color_b = color(1, 1, 1), const Matrix &transformation = identity(), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200);

    // raytrace functions
    virtual const Tuple& get_pattern(const Tuple &pos) const override;
};

#endif