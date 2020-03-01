#include "scene/lighting.h"

const Tuple lighting(const Material &mat, const PointLight &light, const Tuple &pos, const Tuple &eye, const Tuple &normal)
{
    Tuple effective_color = hadamard_product(mat.get_color(), light.get_intensity());

    Tuple ambient = effective_color * mat.get_ambient();

    Tuple light_direction = normalize(light.get_position() - pos);
    double light_dot_normal = dot(light_direction, normal);
    if (light_dot_normal < 0)
	return ambient;
    else
    {
	Tuple diffuse = effective_color * mat.get_diffuse() * light_dot_normal;

	Tuple reflection = reflect(-light_direction, normal);
	double reflection_dot_eye = dot(reflection, eye);
	if (reflection_dot_eye <= 0)
	    return ambient + diffuse;
	else
	{
	    Tuple specular = light.get_intensity() * mat.get_specular() * pow(reflection_dot_eye, mat.get_shininess());
	    return ambient + diffuse + specular;
	}
    }
}