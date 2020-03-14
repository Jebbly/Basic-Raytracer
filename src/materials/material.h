#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"

class Material
{
protected:
    // attributes
    double m_ambient, m_diffuse, m_specular, m_shininess, m_reflective, m_transparency, m_IOR;

public:
    Material(double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR);

    // accessor methods
    double get_ambient() const {return m_ambient;}
    double get_diffuse() const {return m_diffuse;}
    double get_specular() const {return m_specular;}
    double get_shininess() const {return m_shininess;}
    double get_reflective() const {return m_reflective;}
    double get_transparency() const {return m_transparency;}
    double get_IOR() const {return m_IOR;}

    void set_ambient(double ambient);
    void set_diffuse(double diffuse);
    void set_specular(double specular);
    void set_shininess(double shininess);
    void set_reflective(double reflective);
    void set_transparency(double transparency);
    void set_IOR(double IOR);

    // raytrace functions
    virtual Tuple get_color(const Tuple &pos) const = 0;
};

#endif