#include "primitives/cube.h"

// helper function
Tuple Cube::check_axis(double origin, double direction) const
{
    Tuple ret{2};

    double tminmax_numerator[2] = {(-1 - origin), (1 - origin)};
    if (abs(direction) >= Constants::EPSILON)
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] /= direction;
	    ret.set(i, tminmax_numerator[i]);
	}
    }
    else
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] *= INFINITY;
	    ret.set(i, tminmax_numerator[i]);
	}
    }

    if (ret.get(0) > ret.get(1))
    {
	double temp = ret.get(0);
	ret.set(0, ret.get(1));
	ret.set(1, temp);
    }

    return ret;
}

// ray intersect functions
std::vector<Intersection> Cube::local_intersect(const Ray &r) const
{
    Tuple axes[3];
    for (int i = 0; i < 3; i++)
    {
	axes[i] = check_axis(r.get_origin().get(i), r.get_direction().get(i));
    }
    
    double tmin = axes[0].get(0), tmax = axes[0].get(1);
    for (int i = 1; i < 3; i++)
    {
	if (axes[i].get(0) > tmin) tmin = axes[i].get(0);
	if (axes[i].get(1) < tmax) tmax = axes[i].get(1);
    }

    std::vector<Intersection> intersects;
    if (tmin <= tmax)
    {
	intersects.push_back(Intersection{tmin, (Primitive*) this});
	intersects.push_back(Intersection{tmax, (Primitive*) this});
    }
    return intersects;
}

Tuple Cube::local_normal(const Tuple &t) const
{
    double max = 0;
    for (int i = 0; i < 3; i++)
    {
	if (abs(t.get(i)) > max)
	    max = abs(t.get(i));
    }

    Tuple ret = vector(0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
	if (max == abs(t.get(i)))
	    ret.set(i, t.get(i));
    }
    return ret;
}