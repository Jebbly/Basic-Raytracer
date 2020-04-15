#include "scene/world.h"

scene::World::World(const image::Color &ambient) :
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
    math::Tuple4d light_dir = light->direction(position);
    double distance = light_dir.magnitude();
    math::Tuple4d normalized_light_dir = light_dir.normalize();

    std::vector<core::Intersection> xs = intersects(core::Ray{position, normalized_light_dir});
    auto i = hit(xs);
    if (i)
	return (i.value().t() < distance);
    else
	return false;
}

image::Color scene::World::reflection(const core::Computation &comp, int recursion_depth) const
{
    if (utility::equals(comp.object()->material->reflective, 0))
	return image::Color{0, 0, 0};

    return final_color(core::Ray{comp.over_point(), comp.reflect()}, recursion_depth + 1) * comp.object()->material->reflective;
}

image::Color scene::World::refraction(const core::Computation &comp, int recursion_depth) const
{
    if (utility::equals(comp.object()->material->transparency, 0))
	return image::Color{0, 0, 0};

    double n_ratio = comp.n1() / comp.n2();
    double cos_i = dot(comp.eye(), comp.normal());
    double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));

    if (sin2_t > 1)
	return image::Color{0, 0, 0};

    double cos_t = sqrt(1 - sin2_t);
    math::Tuple4d refract = comp.normal() * (n_ratio * cos_i - cos_t) - comp.eye() * n_ratio;
    return final_color(core::Ray{comp.under_point(), refract}, recursion_depth + 1) * comp.object()->material->transparency;
}

double scene::World::schlick(const core::Computation &comp) const
{
    double cos = dot(comp.eye(), comp.normal());

    double n1 = comp.n1(), n2 = comp.n2();
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

image::Color scene::World::shade(const core::Computation &comp, int recursion_depth) const
{
    image::Color ret{0, 0, 0};

    // surface
    for (int i = 0; i < m_lights.size(); i++)
    {
	bool shadowed = shadow(m_lights.at(i), comp.over_point());
	if (!shadowed)
	    ret += m_lights.at(i)->lighting(comp);
    }

    // reflection and refraction
    if (recursion_depth < 5)
    {
	image::Color reflected = reflection(comp, recursion_depth);
	image::Color refracted = refraction(comp, recursion_depth);

	std::shared_ptr<material::Material> mat = comp.object()->material;
	if (mat->reflective > 0 && mat->transparency > 0)
	{
	    double reflectance = schlick(comp);
	    ret += reflected * reflectance + refracted * (1 - reflectance);
	}
	else
	    ret += reflected + refracted;
    }

    // ambient
    ret += image::hadamard_product(m_ambient, comp.object()->color(comp.point())) * comp.object()->material->ambient;

    return ret;
}

image::Color scene::World::final_color(const core::Ray &ray, int recursion_depth) const
{
    std::vector<core::Intersection> xs = intersects(ray);
    auto intersect = core::hit(xs);
    if (intersect)
	return shade(core::Computation{ray, intersect.value(), xs}, recursion_depth);
    else
	return image::Color{0, 0, 0};
}
