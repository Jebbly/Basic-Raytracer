#include <iostream>
#include <chrono>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "core/intersection.h"
#include "scene/light.h"
#include "scene/point_light.h"
#include "scene/world.h"
#include "image/camera.h"

int main()
{
    World w{};

    Material floorMaterial{color(1, 0.9, 0.9), 0.1, 0.9, 1, 200};
    Plane floor{identity(), floorMaterial};

    w.add_object(floor);

    Sphere middle{identity().translate(-0.5, 1, 0.5), Material{color(0.1, 1, 0.5), 0.1, 0.7, 1, 200}};
    Sphere right{identity().scale(0.5, 0.5, 0.5).translate(1.2, 0.5, -0.5), Material{color(0.5, 1, 0.1), 0.1, 0.7, 1, 32}};
    Sphere left{identity().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75), Material{color(1, 0.8, 0.1), 0.1, 0.7, 1, 64}};

    w.add_object(middle);
    w.add_object(right);
    w.add_object(left);

    PointLight light{color(1, 1, 1), point(-2, 2, -2)};
    PointLight light2{color(1, 1, 1), point(10, 10, -10)};

    w.add_light(light);
    w.add_light(light2);

    Camera c{2000, 1000, Constants::PI / 3};
    Tuple from = point(0, 1.5, -5);
    Tuple to = point(0, 1, 0);
    Tuple up = vector(0, 1, 0);
    c.set_transform(view(from, to, up));
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Rendering...\n";
    Framebuffer image = c.render(w);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Finished in " << (std::chrono::duration_cast<std::chrono::seconds>(stop - start)).count() << " seconds\n";
    image.save_buffer("output.ppm");

    return 1;
}