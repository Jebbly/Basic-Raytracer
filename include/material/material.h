#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"
#include "image/color.h"

namespace material
{

class Material
{
public:
    // attributes
    double ambient, diffuse, specular, shininess, reflective, transparency, IOR;

    Material(double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR);

    // raytrace functions
    virtual image::Color color(const math::Tuple4d &point) const = 0;
};

} // namespace material

#endif
