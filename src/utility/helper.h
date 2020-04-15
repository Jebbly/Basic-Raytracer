#ifndef HELPER_H
#define HELPER_H

#include <array>
#include <cmath>
#include <utility>
#include "utility/constants.h"
#include "core/ray.h"

namespace utility
{

// equality comparison
bool equals(double a, double b);

// intersection helper functions
std::array<double, 2> check_axis(double origin, double direction, double min = -1, double max = 1);
std::array<std::pair<double, double>, 2> intersect_caps(const core::Ray &ray, const double y_bounds[2]);

} // namespace utility

#endif
