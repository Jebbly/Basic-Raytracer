#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"

class Material
{
protected:
    // attributes
    double m_ambient, m_diffuse, m_specular, m_shininess, m_reflective;

public:
    Material(double ambient, double diffuse, double specular, double shininess, double reflective);

    // accessor methods
    double get_ambient() const {return m_ambient;}
    double get_diffuse() const {return m_diffuse;}
    double get_specular() const {return m_specular;}
    double get_shininess() const {return m_shininess;}
    double get_reflective() const {return m_reflective;}

    void set_ambient(double ambient);
    void set_diffuse(double diffuse);
    void set_specular(double specular);
    void set_shininess(double shininess);
    void set_reflective(double reflective);

    // raytrace functions
    virtual Tuple get_color(const Tuple &pos) const = 0;
};

#endif