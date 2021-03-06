#ifndef COLOR_MATERIAL_H
#define COLOR_MATERIAL_H

#include "math/tuple.h"
#include "image/color.h"
#include "material/material.h"

namespace material
{

class ColorMaterial : public Material
{
private:
    // attributes
    image::Color m_color;

public:
    ColorMaterial(const image::Color &color = image::Color{0.8, 0.8, 0.8}, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200, double reflective = 0.0, double transparency = 0.0, double IOR = 1.0);

    // accessor methods
    virtual image::Color color(const math::Tuple4d &point) const override;
};

} // namespace material

#endif
