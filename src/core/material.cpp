#include "core/material.h"

Material::Material() : 
    m_color{color(255, 255, 255)},
    m_ambient{1},
    m_diffuse{0},
    m_specular{0},
    m_shininess{0}
{}

// accessor methods
void Material::set_color(const Tuple &color)
{
    m_color = color;
}

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