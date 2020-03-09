#ifndef MATERIAL_H
#define MATERIAL_H

#include "math/tuple.h"
#include "materials/pattern.h"

class Material
{
private:
    // attributes
    Tuple m_color;
    double m_ambient, m_diffuse, m_specular, m_shininess;
    Pattern* m_pattern;

public:
    Material(const Tuple &color = color(1, 1, 1), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200.0);
    Material(const Pattern *pattern, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200);

    // accessor methods
    const Tuple& get_color() const {return m_color;}
    double get_ambient() const {return m_ambient;}
    double get_diffuse() const {return m_diffuse;}
    double get_specular() const {return m_specular;}
    double get_shininess() const {return m_shininess;}
    const Pattern* get_pattern() const {return m_pattern;}

    void set_color(const Tuple &color);
    void set_ambient(double ambient);
    void set_diffuse(double diffuse);
    void set_specular(double specular);
    void set_shininess(double shininess);
    void set_pattern(const Pattern *pattern);
};

#endif