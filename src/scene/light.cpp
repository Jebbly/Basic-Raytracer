#include "scene/light.h"

Light::Light(const Tuple &intensity) :
    m_intensity{intensity}
{}

// phong shading
const Tuple Light::phong_shading(const Material &mat, const Tuple &position, const Tuple &eye, const Tuple &normal) const
{
    Tuple light_direction = get_direction(position);
    double light_dot_normal = dot(light_direction, normal);
    if (light_dot_normal < 0)
	return color(0, 0, 0);
    else
    {
	Tuple effective_color = hadamard_product(mat.get_color(), m_intensity);

	Tuple diffuse = effective_color * mat.get_diffuse() * light_dot_normal;

	Tuple reflect_direction = reflect(-light_direction, normal);
	double reflect_dot_eye = dot(reflect_direction, eye);
	if (reflect_dot_eye <= 0)
	    return diffuse;
	else
	{
	    Tuple specular = m_intensity * mat.get_specular() * pow(reflect_dot_eye, mat.get_shininess());
	    return diffuse + specular;
	}
    }
}