#ifndef HELPER_H
#define HELPER_H

#include <cmath>
#include <vector>
#include "math/tuple.h"
#include "core/ray.h"

// intersection helper functions
math::Tuple2d check_axis(double origin, double direction, double min = -1, double max = 1);
math::Tuple4d intersect_caps(const Ray &r, const double y_bounds[2]);

#endif