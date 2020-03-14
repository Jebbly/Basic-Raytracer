#ifndef PATTERN_H
#define PATTERN_H

#include "math/tuple.h"
#include "math/matrix.h"
#include "materials/material.h"

class Pattern : public Material
{
protected:
    // attributes
    Tuple m_color_a, m_color_b;
    Matrix m_transformation;

public:
    Pattern(const Tuple &color_a = color(0, 0, 0), const Tuple &color_b = color(1, 1, 1), const Matrix &transformation = identity(), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0.0, double IOR = 1.0);

    // accessor methods
    const Matrix& get_transformation() const {return m_transformation;}

    void set_transformation(const Matrix &transformation);

    // raytrace functions
    virtual Tuple get_color(const Tuple &pos) const override;
    virtual Tuple get_pattern(const Tuple &pos) const = 0;
};

#endif