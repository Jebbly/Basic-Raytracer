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

    // accessor methods
    const Tuple& color() const {return m_color;}
    double ambient() const {return m_ambient;}
    double diffuse() const {return m_diffuse;}
    double specular() const {return m_specular;}
    double shininess() const {return m_shininess;}
};

#endif