#include "primitives/cube.h"

// ray intersect functions
std::vector<Intersection> Cube::local_intersect(const Ray &r) const
{
    math::Tuple2d axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = check_axis(r.get_origin()(i), r.get_direction()(i));
    }
    
    double tmin = axes[0](0), tmax = axes[0](1);
    for (int i = 1; i < 3; i++)
    {
	if (axes[i](0) > tmin) tmin = axes[i](0);
	if (axes[i](1) < tmax) tmax = axes[i](1);
    }

    std::vector<Intersection> intersects;
    if (tmin <= tmax)
    {
	intersects.push_back(Intersection{tmin, (Primitive*) this});
	intersects.push_back(Intersection{tmax, (Primitive*) this});
    }
    return intersects;
}

math::Tuple4d Cube::local_normal(const math::Tuple4d &t, const Intersection &hit) const
{
    double max = 0;
    for (int i = 0; i < 3; i++)
    {
	if (abs(t(i)) > max)
	    max = abs(t(i));
    }

    math::Tuple4d ret = math::vector<double>(0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
	if (max == abs(t(i)))
	    ret(i) = t(i);
    }
    return ret;
}

// utility functions
BoundingBox Cube::local_bounds() const
{
    return BoundingBox{math::point<double>(-1, -1, -1), math::point<double>(1, 1, 1)};
}