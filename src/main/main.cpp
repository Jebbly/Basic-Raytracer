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
#include "image/camera.h"

int main()
{
    World w{};
    Camera c{501, 501, Constants::PI / 2};
    Tuple from = point(0, 0, -10);
    Tuple to = point(0, 0, 0);
    Tuple up = vector(0, 1, 0);
    c.set_transform(view(from, to, up));
    Framebuffer image = c.render(w);
    image.save_buffer("output.ppm");
    return 1;
}