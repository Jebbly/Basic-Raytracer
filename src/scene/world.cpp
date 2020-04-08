#include "scene/world.h"

scene::World::World(const math::Tuple3d &ambient) :
    m_ambient{ambient}
{}

// accessor methods
void scene::World::add_object(geometry::primitive::Primitive &object)
{
    m_objects.push_back(&object);
}

void scene::World::add_light(light::Light &light)
{
    m_lights.push_back(&light);
}

// raytrace functions
std::vector<core::Intersection> scene::World::intersects(const core::Ray &ray) const
{
    std::vector<core::Intersection> ret;
    for (int i = 0; i < m_objects.size(); i++)
    {
	std::vector<core::Intersection> object_intersects = m_objects.at(i)->intersect(ray);
	ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

bool scene::World::shadow(const light::Light *light, const math::Tuple4d &position) const
{
    math::Tuple4d light_dir = light->get_direction(position);
    double distance = light_dir.magnitude();
    math::Tuple4d normalized_light_dir = light_dir.normalize();

    std::vector<core::Intersection> xs = intersects(core::Ray{position, normalized_light_dir});
    auto i = hit(xs);
    if (i)
	return (i.value().get_t() < distance);
    else
	return false;
}

math::Tuple3d scene::World::reflection(const core::Computation &comp, int recursion_depth) const
{
    if (utility::equals(comp.get_object()->get_material()->get_reflective(), 0))
	return math::color<double>(0, 0, 0);

    return final_color(core::Ray{comp.get_over_point(), comp.get_reflect()}, recursion_depth + 1) * comp.get_object()->get_material()->get_reflective();
}

math::Tuple3d scene::World::refraction(const core::Computation &comp, int recursion_depth) const
{
    if (utility::equals(comp.get_object()->get_material()->get_transparency(), 0))
	return math::color<double>(0, 0, 0);

    double n_ratio = comp.get_n1() / comp.get_n2();
    double cos_i = dot(comp.get_eye(), comp.get_normal());
    double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));

    if (sin2_t > 1)
	return math::color<double>(0, 0, 0);

    double cos_t = sqrt(1 - sin2_t);
    math::Tuple4d refract = comp.get_normal() * (n_ratio * cos_i - cos_t) - comp.get_eye() * n_ratio;
    return final_color(core::Ray{comp.get_under_point(), refract}, recursion_depth + 1) * comp.get_object()->get_material()->get_transparency();
}

double scene::World::schlick(const core::Computation &comp) const
{
    double cos = dot(comp.get_eye(), comp.get_normal());

    double n1 = comp.get_n1(), n2 = comp.get_n2();
    if (n1 > n2)
    {
	double n = n1 / n2;
	double sin2_t = pow(n, 2) * (1 - pow(cos, 2));
	if (sin2_t > 1) return 1.0;

	double cos_t = sqrt(1 - sin2_t);
	cos = cos_t;
    }

    double r0 = pow((n1 - n2) / (n1 + n2), 2);
    return (r0 + (1 - r0) * pow(1 - cos, 5));
}

math::Tuple3d scene::World::shade(const core::Computation &comp, int recursion_depth) const
{
    math::Tuple3d ret{math::color<double>(0, 0, 0)};

    // surface
    for (int i = 0; i < m_lights.size(); i++)
    {
	bool shadowed = shadow(m_lights.at(i), comp.get_over_point());
	if (!shadowed)
	    ret += m_lights.at(i)->lighting(comp);
    }

    // reflection and refraction
    if (recursion_depth < 5)
    {
	math::Tuple3d reflected = reflection(comp, recursion_depth);
	math::Tuple3d refracted = refraction(comp, recursion_depth);

	std::shared_ptr<material::Material> mat = comp.get_object()->get_material();
	if (mat->get_reflective() > 0 && mat->get_transparency() > 0)
	{
	    double reflectance = schlick(comp);
	    ret += reflected * reflectance + refracted * (1 - reflectance);
	}
	else
	    ret += reflected + refracted;
    }

    // ambient
    ret += math::hadamard_product<double, 3>(m_ambient, comp.get_object()->color(comp.get_point())) * comp.get_object()->get_material()->get_ambient();

    return ret;
}

math::Tuple3d scene::World::final_color(const core::Ray &ray, int recursion_depth) const
{
    std::vector<core::Intersection> xs = intersects(ray);
    auto intersect = core::hit(xs);
    if (intersect)
	return shade(core::Computation{ray, intersect.value(), xs}, recursion_depth);
    else
	return math::color<double>(0, 0, 0);
}