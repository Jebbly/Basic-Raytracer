#include "utility/helper.h"

// equality comparison
bool utility::equals(double a, double b)
{
    if (std::abs(a - b) < constants::EPSILON)
	return true;
    else
	return false;
}

// intersection helper functions
std::array<double, 2> utility::check_axis(double origin, double direction, double min, double max)
{
    std::array<double, 2> ret{};

    double tminmax_numerator[2] = {(min - origin), (max - origin)};
    if (std::abs(direction) >= constants::EPSILON)
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] /= direction;
	    ret[i] = tminmax_numerator[i];
	}
    }
    else
    {
	for (int i = 0; i < 2; i++)
	{
	    tminmax_numerator[i] *= INFINITY;
	    ret[i] = tminmax_numerator[i];
	}
    }

    if (ret[0] > ret[1])
    {
	double temp = ret[0];
	ret[0] = ret[1];
	ret[1] = temp;
    }

    return ret;
}

std::array<std::pair<double, double>, 2> utility::intersect_caps(const core::Ray &ray, const double y_bounds[2])
{
    double y_direction = ray.direction()(1);
    double y_origin = ray.origin()(1);

    std::array<std::pair<double, double>, 2> ret{};
    for (int i = 0; i < 2; i++)
    {
	double t = (y_bounds[i] - y_origin) / y_direction;
	math::Tuple4d pos = ray.position(t);
	ret[i] = std::make_pair(sqrt(pow(pos(0), 2) + pow(pos(2), 2)), t);
    }
    return ret;
}
