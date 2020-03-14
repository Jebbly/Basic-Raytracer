#include "materials/material.h"

Material::Material(double ambient, double diffuse, double specular, double shininess, double reflective) : 
    m_ambient{ambient},
    m_diffuse{diffuse},
    m_specular{specular},
    m_shininess{shininess},
    m_reflective{reflective}
{}

// accessor methods
void Material::set_ambient(double ambient)
{
    m_ambient = ambient;
}

void Material::set_diffuse(double diffuse)
{
    m_diffuse = diffuse;
}
void Material::set_specular(double specular)
{
    m_specular = specular;
}

void Material::set_shininess(double shininess)
{
    m_shininess = shininess;
}

void Material::set_reflective(double reflective)
{
    m_reflective = reflective;
}