#include "core/intersection.h"

Intersection::Intersection(double t, const Sphere &object) :
    m_t{t},
    m_object{object}
{}

// comparison overload
bool operator<(const Intersection &i1, const Intersection &i2)
{
    return (i1.m_t < i2.m_t);
}

// utility functions
std::vector<Intersection> intersections(const Ray &r, const Sphere &s)
{
    Tuple t_values = s.intersect(r);
    
    std::vector<Intersection> intersects{};
    for (int i = 0; i < t_values.get_size(); i++)
    {
	intersects.push_back(Intersection{t_values.get(i), s});
    }

    std::sort(intersects.begin(), intersects.end());
    return intersects;
}

std::optional<const Intersection> hit(const std::vector<Intersection> &intersections)
{
    for (int i = 0; i < intersections.size(); i++)
    {
	if (intersections.at(i).t() > 0)
	    return intersections.at(i);
    }

    return std::nullopt;
}