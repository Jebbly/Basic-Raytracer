#include "scene/lights/light.h"

scene::light::Light::Light(const image::Color &intensity) :
    m_intensity{intensity}
{}

// phong shading
const image::Color scene::light::Light::phong_shading(geometry::primitive::Primitive *object, const math::Tuple4d &position, const math::Tuple4d &eye, const math::Tuple4d &normal) const
{
    math::Tuple4d light_direction = get_direction(position);
    double light_dot_normal = dot(light_direction, normal);
    if (light_dot_normal < 0)
	return image::Color{0, 0, 0};
    else
    {
	image::Color effective_color = image::hadamard_product(object->color(position), m_intensity);
	std::shared_ptr<material::Material> mat = object->get_material();

	image::Color diffuse = effective_color * mat->get_diffuse() * light_dot_normal;

	math::Tuple4d reflect_direction = math::reflect(-light_direction, normal);
	double reflect_dot_eye = dot(reflect_direction, eye);
	if (reflect_dot_eye <= 0)
	    return diffuse;
	else
	{
	    image::Color specular = m_intensity * mat->get_specular() * pow(reflect_dot_eye, mat->get_shininess());
	    return diffuse + specular;
	}
    }
}