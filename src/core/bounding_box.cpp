#include "core/bounding_box.h"

BoundingBox::BoundingBox(const math::Tuple4d &minimum, const math::Tuple4d &maximum) :
    m_minmax{minimum, maximum}
{}

// accessor methods
const math::Tuple4d& BoundingBox::get_minimum() const
{
    return m_minmax[0];
}

const math::Tuple4d& BoundingBox::get_maximum() const
{
    return m_minmax[1];
}

void BoundingBox::set_minimum(const math::Tuple4d &t)
{
    m_minmax[0] = t;
}

void BoundingBox::set_maximum(const math::Tuple4d &t)
{
    m_minmax[1] = t;
}

// utility functions
void BoundingBox::add_point(const math::Tuple4d &point)
{
    // test for minimums
    for (int i = 0; i < 3; i++)
    {
	if (point(i) < m_minmax[0](i))
	    m_minmax[0](i) = point(i);
    }

    // test for maximums
    for (int i = 0; i < 3; i++)
    {
	if (point(i) > m_minmax[1](i))
	    m_minmax[1](i) = point(i);
    }
}

bool BoundingBox::contains_point(const math::Tuple4d &point) const
{
    for (int i = 0; i < 3; i++)
    {
	if (point(i) < m_minmax[0](i) ||
	    point(i) > m_minmax[1](i))
	    return false;
    }
    return true;
}

void BoundingBox::add_bounds(const BoundingBox &box)
{
    add_point(box.get_minimum());
    add_point(box.get_maximum());
}

bool BoundingBox::contains_bounds(const BoundingBox &box) const
{
    return (contains_point(box.get_minimum()) && contains_point(box.get_maximum()));;
}

BoundingBox BoundingBox::transform(const math::Matrix4d &transformation)
{
    math::Tuple4d original_points[8];

    int idx = 0;
    for (int i = 0; i < 2; i++)
    {
	for (int j = 0; j < 2; j++)
	{
	    for (int k = 0; k < 2; k++)
	    {
		original_points[idx++] = math::point<double>(m_minmax[i](0), m_minmax[j](1), m_minmax[k](2));
	    }
	}
    }

    BoundingBox ret{};
    for (int i = 0; i < 8; i++)
    {
	ret.add_point(transformation * original_points[i]);
    }
    return ret;
}

bool BoundingBox::intersect(const Ray &r) const
{
    math::Tuple2d axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = utility::check_axis(r.get_origin()(i), r.get_direction()(i), m_minmax[0](i), m_minmax[1](i));
    }

    double tmin = axes[0](0), tmax = axes[0](1);
    for (int i = 1; i < 3; i++)
    {
	if (axes[i](0) > tmin) tmin = axes[i](0);
	if (axes[i](1) < tmax) tmax = axes[i](1);
    }

    return (tmin <= tmax);
}