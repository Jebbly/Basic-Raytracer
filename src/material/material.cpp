#include "material/material.h"

material::Material::Material(double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) : 
    m_ambient{ambient},
    m_diffuse{diffuse},
    m_specular{specular},
    m_shininess{shininess},
    m_reflective{reflective},
    m_transparency{transparency},
    m_IOR{IOR}
{}

// accessor methods
void material::Material::set_ambient(double ambient)
{
    m_ambient = ambient;
}

void material::Material::set_diffuse(double diffuse)
{
    m_diffuse = diffuse;
}
void material::Material::set_specular(double specular)
{
    m_specular = specular;
}

void material::Material::set_shininess(double shininess)
{
    m_shininess = shininess;
}

void material::Material::set_reflective(double reflective)
{
    m_reflective = reflective;
}

void material::Material::set_transparency(double transparency)
{
    m_transparency = transparency;
}

void material::Material::set_IOR(double IOR)
{
    m_IOR = IOR;
}