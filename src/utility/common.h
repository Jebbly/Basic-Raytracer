#ifndef COMMON_H
#define COMMON_H

#include <cassert>
#include <cmath>

namespace constants
{
    constexpr double EPSILON{0.00001};
    constexpr double PI{3.14159};
}

bool equals(double a, double b);

#endif