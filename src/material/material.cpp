#include "material/material.h"

material::Material::Material(double ambient, double diffuse, double specular, double shininess, double reflective, double transparency, double IOR) : 
    ambient{ambient},
    diffuse{diffuse},
    specular{specular},
    shininess{shininess},
    reflective{reflective},
    transparency{transparency},
    IOR{IOR}
{}
