#include "scene/world.h"

World::World(const Tuple &ambient) :
    m_ambient{ambient}
{}

// accessor methods
void World::add_object(Primitive &object)
{
    m_objects.push_back(&object);
}

void World::add_light(Light &light)
{
    m_lights.push_back(&light);
}

// raytrace functions
std::vector<Intersection> World::intersects(const Ray &ray) const
{
    std::vector<Intersection> ret;
    for (int i = 0; i < m_objects.size(); i++)
    {
	std::vector<Intersection> object_intersects = m_objects.at(i)->intersect(ray);
	ret.insert(ret.end(), object_intersects.begin(), object_intersects.end());
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}

bool World::shadow(const Light *light, const Tuple &position) const
{
    Tuple light_dir = light->get_direction(position);
    double distance = magnitude(light_dir);
    Tuple normalized_light_dir = normalize(light_dir);

    std::vector<Intersection> xs = intersects(Ray{position, normalized_light_dir});
    auto i = hit(xs);
    if (i)
	return (i.value().get_t() < distance);
    else
	return false;
}

Tuple World::reflection(const Computation &comp, int recursion_depth) const
{
    if (equals(comp.get_object()->get_material()->get_reflective(), 0))
	return color(0, 0, 0);

    return final_color(Ray{comp.get_over_point(), comp.get_reflect()}, recursion_depth + 1) * comp.get_object()->get_material()->get_reflective();
}

Tuple World::refraction(const Computation &comp, int recursion_depth) const
{
    if (equals(comp.get_object()->get_material()->get_transparency(), 0))
	return color(0, 0, 0);

    double n_ratio = comp.get_n1() / comp.get_n2();
    double cos_i = dot(comp.get_eye(), comp.get_normal());
    double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));

    if (sin2_t > 1)
	return color(0, 0, 0);

    double cos_t = sqrt(1 - sin2_t);
    Tuple refract = comp.get_normal() * (n_ratio * cos_i - cos_t) - comp.get_eye() * n_ratio;
    return final_color(Ray{comp.get_under_point(), refract}, recursion_depth + 1) * comp.get_object()->get_material()->get_transparency();
}

double World::schlick(const Computation &comp) const
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

Tuple World::shade(const Computation &comp, int recursion_depth) const
{
    Tuple ret{color(0, 0, 0)};

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
	Tuple reflected = reflection(comp, recursion_depth);
	Tuple refracted = refraction(comp, recursion_depth);

	std::shared_ptr<Material> mat = comp.get_object()->get_material();
	if (mat->get_reflective() > 0 && mat->get_transparency() > 0)
	{
	    double reflectance = schlick(comp);
	    ret += reflected * reflectance + refracted * (1 - reflectance);
	}
	else
	    ret += reflected + refracted;
    }

    // ambient
    ret += hadamard_product(m_ambient, comp.get_object()->color(comp.get_point())) * comp.get_object()->get_material()->get_ambient();

    return ret;
}

Tuple World::final_color(const Ray &ray, int recursion_depth) const
{
    std::vector<Intersection> xs = intersects(ray);
    auto intersect = hit(xs);
    if (intersect)
	return shade(Computation{ray, intersect.value(), xs}, recursion_depth);
    else
	return color(0, 0, 0);
}