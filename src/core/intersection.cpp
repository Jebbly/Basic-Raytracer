#include "core/intersection.h"

Intersection::Intersection(double t, geometry::primitive::Primitive *object, std::pair<double, double> uv) :
    m_t{t},
    m_object{object},
    m_uv{uv}
{}

// accessor methods
double Intersection::get_t() const
{
    return m_t;
}

geometry::primitive::Primitive* Intersection::get_object() const
{
    return m_object;
}

const std::pair<double, double>& Intersection::get_uv() const
{
    return m_uv;
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