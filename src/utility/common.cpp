#include "utility/common.h"

bool equals(double a, double b)
{
    if (abs(a - b) < constants::EPSILON)
	return true;
    else
	return false;
}