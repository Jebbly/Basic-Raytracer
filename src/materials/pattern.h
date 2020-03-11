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

    Pattern(const Tuple &color_a, const Tuple &color_b, const Matrix &transformation, double ambient, double diffuse, double specular, double shininess);

public:
    // accessor methods
    const Matrix& get_transformation() const {return m_transformation;}

    void set_transformation(const Matrix &transformation);

    // raytrace functions
    virtual Tuple get_color(const Tuple &pos) const override;
    virtual Tuple get_pattern(const Tuple &pos) const = 0;
};

#endif