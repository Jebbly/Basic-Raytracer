#include "core/bounding_box.h"

BoundingBox::BoundingBox(const Tuple &minimum, const Tuple &maximum) :
    m_minmax{minimum, maximum}
{}

// helper functions
void BoundingBox::add_point(const Tuple &point)
{
    // test for minimums
    for (int i = 0; i < 3; i++)
    {
	if (point.get(i) < m_minmax[0].get(i))
	    m_minmax[0].set(i, point.get(i));
    }

    // test for maximums
    for (int i = 0; i < 3; i++)
    {
	if (point.get(i) > m_minmax[1].get(i))
	    m_minmax[1].set(i, point.get(i));
    }
}

bool BoundingBox::contains_point(const Tuple &point) const
{
    for (int i = 0; i < 3; i++)
    {
	if (point.get(i) < m_minmax[0].get(i) ||
	    point.get(i) > m_minmax[1].get(i))
	    return false;
    }
    return true;
}

// accessor methods
const Tuple& BoundingBox::get_minimum() const
{
    return m_minmax[0];
}

const Tuple& BoundingBox::get_maximum() const
{
    return m_minmax[1];
}

void BoundingBox::set_minimum(const Tuple &t)
{
    m_minmax[0] = t;
}

void BoundingBox::set_maximum(const Tuple &t)
{
    m_minmax[1] = t;
}

// utility functions
void BoundingBox::add_bounds(const BoundingBox &box)
{
    add_point(box.get_minimum());
    add_point(box.get_maximum());
}

bool BoundingBox::contains_bounds(const BoundingBox &box) const
{
    return (contains_point(box.get_minimum()) && contains_point(box.get_maximum()));;
}

BoundingBox BoundingBox::transform(const Matrix &transformation)
{
    Tuple original_points[8];

    int idx = 0;
    for (int i = 0; i < 2; i++)
    {
	for (int j = 0; j < 2; j++)
	{
	    for (int k = 0; k < 2; k++)
	    {
		original_points[idx++] = point(m_minmax[i].get(0), m_minmax[j].get(1), m_minmax[k].get(2));
	    }
	}
    }

    BoundingBox ret{};
    for (int i = 0; i < 8; i++)
    {
	ret.add_point(multiply(transformation, original_points[i]));
    }
    return ret;
}

bool BoundingBox::intersect(const Ray &r) const
{
    Tuple axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = check_axis(r.get_origin().get(i), r.get_direction().get(i), m_minmax[0].get(i), m_minmax[1].get(i));
    }

    double tmin = axes[0].get(0), tmax = axes[0].get(1);
    for (int i = 1; i < 3; i++)
    {
	if (axes[i].get(0) > tmin) tmin = axes[i].get(0);
	if (axes[i].get(1) < tmax) tmax = axes[i].get(1);
    }

    return (tmin <= tmax);
}