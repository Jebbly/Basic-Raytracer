#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "core/intersection.h"
#include "scene/lighting.h"
#include "scene/world.h"

int main()
{
    Tuple from = point(1, 3, 2);
    Tuple to = point(4, -2, 8);
    Tuple up = vector(1, 1, 0);
    std::cout << view(from, to, up);
    return 1;
}