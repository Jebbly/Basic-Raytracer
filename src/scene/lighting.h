#ifndef LIGHTING_H
#define LIGHTING_H

#include <cmath>
#include "math/tuple.h"
#include "core/material.h"
#include "scene/point_light.h"

const Tuple lighting(const Material &mat, const PointLight &light, const Tuple &pos, const Tuple &eye, const Tuple &normal);

#endif