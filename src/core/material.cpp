#include "core/material.h"

Material::Material() : 
    m_color{color(1, 1, 1)},
    m_ambient{1},
    m_diffuse{0},
    m_specular{0},
    m_shininess{0}
{}