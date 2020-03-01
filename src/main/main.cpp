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
    std::vector<Intersection> xs = w.intersects(Ray{point(0, 0, -5), vector(0, 0, 1)});
    for (int i = 0; i < xs.size(); i++)
    {
	std::cout << xs.at(i).get_t() << "\n";
    }
    return 1;
}