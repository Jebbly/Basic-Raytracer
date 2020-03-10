#ifndef STRIPE_MATERIAL_H
#define STRIPE_MATERIAL_H

#include "math/tuple.h"
#include "materials/material.h"

class StripeMaterial : public Material
{
private:
    // attributes
    Tuple m_color_a, m_color_b;

public:
    StripeMaterial(const Tuple &color_a = color(0, 0, 0), const Tuple &color_b = color(1, 1, 1), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200);

    // accessor methods
    virtual const Tuple& get_color(const Tuple &pos) const override;
};

#endif