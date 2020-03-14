#ifndef COLOR_MATERIAL_H
#define COLOR_MATERIAL_H

#include "math/tuple.h"
#include "materials/material.h"

class ColorMaterial : public Material
{
private:
    // attributes
    Tuple m_color;

public:
    ColorMaterial(const Tuple &color = color(0.8, 0.8, 0.8), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0.0, double IOR = 1.0);

    // accessor methods
    virtual Tuple get_color(const Tuple &pos) const override;
};

#endif