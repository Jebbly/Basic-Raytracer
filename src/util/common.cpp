#include "util/common.h"

bool equals(double a, double b)
{
    if (abs(a - b) < EPSILON)
	return true;
    else
	return false;
}