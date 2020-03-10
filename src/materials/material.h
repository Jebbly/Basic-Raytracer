#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"

class Material
{
protected:
    // attributes
    double m_ambient, m_diffuse, m_specular, m_shininess;

public:
    Material(double ambient, double diffuse, double specular, double shininess);

    // accessor methods
    virtual const Tuple& get_color() const = 0;

    double get_ambient() const {return m_ambient;}
    double get_diffuse() const {return m_diffuse;}
    double get_specular() const {return m_specular;}
    double get_shininess() const {return m_shininess;}

    void set_ambient(double ambient);
    void set_diffuse(double diffuse);
    void set_specular(double specular);
    void set_shininess(double shininess);
};

#endif