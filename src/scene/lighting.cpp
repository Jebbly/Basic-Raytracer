#include "scene/lighting.h"

const Tuple lighting(const Material &mat, const PointLight &light, const Tuple &pos, const Tuple &eye, const Tuple &normal, bool shadowed)
{
    Tuple effective_color = hadamard_product(mat.get_color(), light.get_intensity());

    Tuple ambient = effective_color * mat.get_ambient();

    Tuple light_direction = normalize(light.get_position() - pos);
    double light_dot_normal = dot(light_direction, normal);
    if (light_dot_normal < 0 || shadowed)
	return ambient;
    else
    {
	Tuple diffuse = effective_color * mat.get_diffuse() * light_dot_normal;

	Tuple reflect_direction = reflect(-light_direction, normal);
	double reflect_dot_eye = dot(reflect_direction, eye);
	if (reflect_dot_eye <= 0)
	    return ambient + diffuse;
	else
	{
	    Tuple specular = light.get_intensity() * mat.get_specular() * pow(reflect_dot_eye, mat.get_shininess());
	    return ambient + diffuse + specular;
	}
    }
}