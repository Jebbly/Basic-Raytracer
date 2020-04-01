#include "core/computation.h"

Computation::Computation(const Ray &ray, const Intersection &intersect, const std::vector<Intersection> &xs) :
    m_t{intersect.get_t()},
    m_object{intersect.get_object()},
    m_eye{-ray.get_direction()}
{
    m_point = ray.position(m_t);
    m_normal = m_object->normal(m_point, intersect);

    if (dot(m_normal, m_eye) < 0)
    {
	m_inside = true;
	m_normal = -m_normal;
    }
    else
	m_inside = false;

    std::vector<Primitive*> containers;
    for (int i = 0; i < xs.size(); i++)
    {
	if (xs.at(i) == intersect)
	{
	    if (containers.size() == 0)
		m_n1 = 1.0;
	    else
		m_n1 = containers.at(containers.size() - 1)->get_material()->get_IOR();
	}

	std::vector<Primitive*>::iterator found = std::find(containers.begin(), containers.end(), xs.at(i).get_object());
	if (found != containers.end())
	    containers.erase(found);
	else
	    containers.push_back(xs.at(i).get_object());

	if (xs.at(i) == intersect)
	{
	    if (containers.size() == 0)
		m_n2 = 1.0;
	    else
		m_n2 = containers.at(containers.size() - 1)->get_material()->get_IOR();
	}
    }

    m_reflect = reflect(ray.get_direction(), m_normal);
    m_over_point = m_point + m_normal * Constants::EPSILON;
    m_under_point = m_point - m_normal * Constants::EPSILON;
}