#include "core/intersection.h"

Intersection::Intersection(double t, Primitive *object) :
    m_t{t},
    m_object{object}
{}

// accessor methods
double Intersection::get_t() const
{
    return m_t;
}

Primitive* Intersection::get_object() const
{
    return m_object;
}

// comparison overload
bool operator<(const Intersection &i1, const Intersection &i2)
{
    return (i1.m_t < i2.m_t);
}

bool operator==(const Intersection &i1, const Intersection &i2)
{
    return (i1.m_t == i2.m_t && i1.m_object == i2.m_object);
}

// utility function
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections)
{
    for (int i = 0; i < intersections.size(); i++)
    {
	if (intersections.at(i).get_t() > 0)
	    return intersections.at(i);
    }

    return std::nullopt;
}