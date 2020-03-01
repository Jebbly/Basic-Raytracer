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
    World w{};
    Ray r{point(0, 0, -5), vector(0, 0, 1)};
    std::cout << w.final_color(r);
    return 1;
}