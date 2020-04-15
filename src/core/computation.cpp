#include "core/computation.h"

core::Computation::Computation(const Ray &ray, const Intersection &intersect, const std::vector<Intersection> &xs) :
    m_t{intersect.t()},
    m_object{intersect.object()},
    m_eye{-ray.direction()}
{
    m_point = ray.position(m_t);
    m_normal = m_object->normal(m_point, intersect);

    if (dot(m_normal, m_eye) < 0)
	m_normal = -m_normal;

    std::vector<geometry::primitive::Primitive*> containers;
    for (int i = 0; i < xs.size(); i++)
    {
	if (xs.at(i) == intersect)
	{
	    if (containers.size() == 0)
		m_n1 = 1.0;
	    else
		m_n1 = containers.at(containers.size() - 1)->material->IOR;
	}

	std::vector<geometry::primitive::Primitive*>::iterator found = std::find(containers.begin(), containers.end(), xs.at(i).object());
	if (found != containers.end())
	    containers.erase(found);
	else
	    containers.push_back(xs.at(i).object());

	if (xs.at(i) == intersect)
	{
	    if (containers.size() == 0)
		m_n2 = 1.0;
	    else
		m_n2 = containers.at(containers.size() - 1)->material->IOR;
	}
    }

    m_reflect = math::reflect(ray.direction(), m_normal);
    m_over_point = m_point + m_normal * constants::EPSILON;
    m_under_point = m_point - m_normal * constants::EPSILON;
}
