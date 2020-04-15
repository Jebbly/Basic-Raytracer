#include "core/intersection.h"

core::Intersection::Intersection(double t, geometry::primitive::Primitive *object, std::pair<double, double> uv) :
    m_t{t},
    m_object{object},
    m_uv{uv}
{}

// comparison overloads
bool core::operator<(const core::Intersection &i1, const core::Intersection &i2)
{
    return (i1.m_t < i2.m_t);
}

bool core::operator==(const core::Intersection &i1, const core::Intersection &i2)
{
    return (i1.m_t == i2.m_t && i1.m_object == i2.m_object);
}

// utility function
std::optional<const core::Intersection> core::hit(const std::vector<core::Intersection> &intersections)
{
    for (int i = 0; i < intersections.size(); i++)
    {
	if (intersections.at(i).t() > 0)
	    return intersections.at(i);
    }

    return std::nullopt;
}
