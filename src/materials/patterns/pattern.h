#ifndef PATTERN_H
#define PATTERN_H

#include "math/tuple.h"
#include "math/matrix.h"
#include "materials/material.h"

namespace material::pattern
{

class Pattern : public Material
{
protected:
    // attributes
    math::Tuple3d m_color_a, m_color_b;
    math::Matrix4d m_transformation;

public:
    Pattern(const math::Tuple3d &color_a = math::color<double>(0, 0, 0), const math::Tuple3d &color_b = math::color<double>(1, 1, 1), const math::Matrix4d &transformation = math::identity<double, 4>(), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0.0, double IOR = 1.0);

    // accessor methods
    const math::Matrix4d& get_transformation() const { return m_transformation; }

    void set_transformation(const math::Matrix4d &transformation);

    // raytrace functions
    virtual math::Tuple3d get_color(const math::Tuple4d &pos) const override;
    virtual math::Tuple3d get_pattern(const math::Tuple4d &pos) const = 0;
};

} // namespace material::pattern

#endif