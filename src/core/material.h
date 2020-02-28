#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"

class Material
{
private:
    // attributes
    Tuple m_color;
    double m_ambient, m_diffuse, m_specular, m_shininess;

public:
    Material();
};

#endif