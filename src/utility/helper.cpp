#include "utility/helper.h"

// intersection helper functions
math::Tuple2d check_axis(double origin, double direction, double min, double max)
{
    math::Tuple2d ret{};

    double tminmax_numerator[2] = {(min - origin), (max - origin)};
    if (abs(direction) >= Constants::EPSILON)
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] /= direction;
	    ret(i) = tminmax_numerator[i];
	}
    }
    else
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] *= INFINITY;
	    ret(i) = tminmax_numerator[i];
	}
    }

    if (ret(0) > ret(1))
    {
	double temp = ret(0);
	ret(0) = ret(1);
	ret(1) = temp;
    }

    return ret;
}

math::Tuple4d intersect_caps(const Ray &r, const double y_bounds[2])
{
    double y_direction = r.get_direction()(1);
    double y_origin = r.get_origin()(1);

    math::Tuple4d ret{};
    for (int i = 0; i < 2; i++)
    {
	double t = (y_bounds[i] - y_origin) / y_direction;
	math::Tuple4d pos = r.position(t);
	ret(2 * i) = sqrt(pow(pos(0), 2) + pow(pos(2), 2));
	ret(2 * i + 1) = t;
    }
    return ret;
}