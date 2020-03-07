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

    Material floorMaterial{color(1, 0.9, 0.9), 0.1, 0.9, 0, 0};
    Sphere floor{identity().scale(10, 0.01, 10), floorMaterial};
    Sphere leftWall{identity().scale(10, 0.01, 10).rotate_x(Constants::PI / 2).rotate_y(-Constants::PI / 4).translate(0, 0, 5), floorMaterial};
    Sphere rightWall{identity().scale(10, 0.01, 10).rotate_x(Constants::PI / 2).rotate_y(Constants::PI / 4).translate(0, 0, 5), floorMaterial};

    w.add_object(floor);
    w.add_object(leftWall);
    w.add_object(rightWall);

    Sphere middle{identity().translate(-0.5, 1, 0.5), Material{color(0.1, 1, 0.5), 0.1, 0.7, 0.3}};
    Sphere right{identity().scale(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5), Material{color(0.5, 1, 0.1), 0.1, 0.7, 0.3}};
    Sphere left{identity().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75), Material{color(1, 0.8, 0.1), 0.1, 0.7, 0.3}};

    w.add_object(middle);
    w.add_object(right);
    w.add_object(left);

    PointLight light{color(1, 1, 1), point(-10, 10, -10)};

    w.add_light(light);

    Camera c{100, 50, Constants::PI / 3};
    Tuple from = point(0, 1.5, -5);
    Tuple to = point(0, 1, 0);
    Tuple up = vector(0, 1, 0);
    c.set_transform(view(from, to, up));
    Framebuffer image = c.render(w);
    image.save_buffer("output.ppm");

    return 1;
}