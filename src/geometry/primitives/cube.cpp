#include "geometry/primitives/cube.h"

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Cube::local_intersect(const core::Ray &r) const
{
    math::Tuple2d axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = utility::check_axis(r.get_origin()(i), r.get_direction()(i));
    }
    
    double tmin = axes[0](0), tmax = axes[0](1);
    for (int i = 1; i < 3; i++)
    {
	if (axes[i](0) > tmin) tmin = axes[i](0);
	if (axes[i](1) < tmax) tmax = axes[i](1);
    }

    std::vector<core::Intersection> intersects;
    if (tmin <= tmax)
    {
	intersects.push_back(core::Intersection{tmin, (Primitive*) this});
	intersects.push_back(core::Intersection{tmax, (Primitive*) this});
    }
    return intersects;
}

math::Tuple4d geometry::primitive::Cube::local_normal(const math::Tuple4d &t, const core::Intersection &hit) const
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
core::BoundingBox geometry::primitive::Cube::local_bounds() const
{
    return core::BoundingBox{math::point<double>(-1, -1, -1), math::point<double>(1, 1, 1)};
}