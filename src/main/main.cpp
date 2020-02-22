#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "core/intersection.h"

int main()
{
    Tuple ray_origin = point(0, 0, -5);
    double wall_z = 10;
    double wall_size = 7;

    Framebuffer canvas{100, 100};
    double pixel_size = (double) 7 / 100;
    double half = wall_size / 2;

    Sphere sph;

    sph.set_transform(identity().translate(0, 1, 0));
    Tuple normal = sph.normal(point(0, 1.70711, -0.70711));
    std::cout << normal << '\n';

    Sphere sph1;
    sph1.set_transform(identity().rotate_z(Constants::PI / 5).scale(1, 0.5, 1));
    Tuple normal1 = sph1.normal(point(0, sqrt(2) / 2, -sqrt(2) / 2));
    std::cout << normal1 << '\n';

    return 1;
}