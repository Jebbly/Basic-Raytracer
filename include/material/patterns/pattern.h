#ifndef PATTERN_H
#define PATTERN_H

#include "math/tuple.h"
#include "math/matrix.h"
#include "image/color.h"
#include "material/material.h"

namespace material::pattern
{

class Pattern : public Material
{
protected:
    // attributes
    image::Color m_color_a, m_color_b;
    math::Matrix4d m_transformation;

public:
    Pattern(const image::Color &color_a = image::Color{0, 0, 0}, const image::Color &color_b = image::Color{1, 1, 1}, const math::Matrix4d &transformation = math::identity(), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0.0, double IOR = 1.0);

    // accessor methods
    void set_transformation(const math::Matrix4d &transformation);

    // raytrace functions
    virtual image::Color color(const math::Tuple4d &point) const override;
    virtual image::Color pattern(const math::Tuple4d &point) const = 0;
};

} // namespace material::pattern

#endif
