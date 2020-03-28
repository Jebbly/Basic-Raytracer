#include "utility/helper.h"

// intersection helper functions
Tuple check_axis(double origin, double direction, double min, double max)
{
    Tuple ret{2};

    double tminmax_numerator[2] = {(min - origin), (max - origin)};
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

Tuple intersect_caps(const Ray &r, const double y_bounds[2])
{
    double y_direction = r.get_direction().get(1);
    double y_origin = r.get_origin().get(1);

    Tuple ret{4};
    for (int i = 0; i < 2; i++)
    {
	double t = (y_bounds[i] - y_origin) / y_direction;
	Tuple pos = r.position(t);
	ret.set(2 * i, sqrt(pow(pos.get(0), 2) + pow(pos.get(2), 2)));
	ret.set(2 * i + 1, t);
    }
    return ret;
}