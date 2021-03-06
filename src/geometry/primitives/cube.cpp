#include "geometry/primitives/cube.h"

// ray intersect functions
std::vector<core::Intersection> geometry::primitive::Cube::local_intersect(const core::Ray &ray) const
{
    std::array<double, 2> axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = utility::check_axis(ray.origin()(i), ray.direction()(i));
    }
    
    double tmin = axes[0][0], tmax = axes[0][1];
    for (int i = 1; i < 3; i++)
    {
	if (axes[i][0] > tmin) tmin = axes[i][0];
	if (axes[i][1] < tmax) tmax = axes[i][1];
    }

    std::vector<core::Intersection> intersects;
    if (tmin <= tmax)
    {
	intersects.push_back(core::Intersection{tmin, (Primitive*) this});
	intersects.push_back(core::Intersection{tmax, (Primitive*) this});
    }
    return intersects;
}

math::Tuple4d geometry::primitive::Cube::local_normal(const math::Tuple4d &point, const core::Intersection &hit) const
{
    double max = 0;
    for (int i = 0; i < 3; i++)
    {
	if (std::abs(point(i)) > max)
	    max = std::abs(point(i));
    }

    math::Tuple4d ret = math::vector(0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
	if (max == std::abs(point(i)))
	    ret(i) = point(i);
    }
    return ret;
}

// utility functions
core::BoundingBox geometry::primitive::Cube::local_bounds() const
{
    return core::BoundingBox{math::point(-1, -1, -1), math::point(1, 1, 1)};
}
