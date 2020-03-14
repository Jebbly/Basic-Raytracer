#include "core/intersection.h"

Intersection::Intersection(double t, const Primitive *object) :
    m_t{t},
    m_object{object}
{}

// comparison overload
bool operator<(const Intersection &i1, const Intersection &i2)
{
    return (i1.m_t < i2.m_t);
}

bool operator==(const Intersection &i1, const Intersection &i2)
{
    return (i1.m_t == i2.m_t && i1.m_object == i2.m_object);
}

// utility functions
Tuple normal(const Primitive *o, const Tuple &t)
{
    Tuple object_point = multiply(o->get_transformation().inverse(), t);
    Tuple object_normal = o->local_normal(object_point);
    Tuple world_normal = multiply(o->get_transformation().inverse().transpose(), object_normal);

    world_normal.set(3, 0.0);
    return normalize(world_normal);
}

std::vector<Intersection> intersect(const Primitive *o, const Ray &r)
{
    Ray transformed_ray = r.transform(o->get_transformation().inverse());
    Tuple t_values = o->local_intersect(transformed_ray);

    std::vector<Intersection> ret;
    for (int i = 0; i < t_values.get_size(); i++)
    {
	ret.push_back(Intersection{t_values.get(i), o});
    }
    return ret;
}

std::optional<const Intersection> hit(const std::vector<Intersection> &intersections)
{
    for (int i = 0; i < intersections.size(); i++)
    {
	if (intersections.at(i).get_t() > 0)
	    return intersections.at(i);
    }

    return std::nullopt;
}