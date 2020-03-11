#include <iostream>
#include <chrono>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "materials/color_material.h"
#include "materials/stripe_material.h"
#include "materials/gradient_material.h"
#include "materials/ring_material.h"
#include "materials/checker_material.h"
#include "core/intersection.h"
#include "scene/light.h"
#include "scene/point_light.h"
#include "scene/world.h"
#include "image/camera.h"

int main()
{
    World w{};

    StripeMaterial stripes{color(215/255.0, 178/255.0, 255/255.0), color(147/255.0, 216/255.0, 148/255.0), identity().scale(0.5, 0.5, 0.5), 0.1, 0.9, 1, 200};
    GradientMaterial gradient{color(0.8, 0, 0), color(0, 0, 0.8), identity().scale(1.5, 1.5, 1.5).rotate_y(Constants::PI / 3)};
    RingMaterial ring{color(211/255.0, 217/255.0, 231/255.0), color(141/255.0, 153/255.0, 186/255.0), identity().scale(0.25, 0.25, 0.25).rotate_x(Constants::PI / 1.5).rotate_y(-Constants::PI / 12)};
    CheckerMaterial grid{color(0.2, 0.2, 0.2), color(0.7, 0.7, 0.7)};
    Plane floor{identity(), &grid};

    w.add_object(floor);

    Sphere middle{identity().translate(-0.5, 1, 0.5), /*Material{color(0.1, 1, 0.5), 0.1, 0.7, 1, 200}*/ &gradient};
    Sphere right{identity().scale(0.5, 0.5, 0.5).translate(1.2, 0.5, -0.5), /*Material{color(0.5, 1, 0.1), 0.1, 0.7, 1, 32}*/ &ring};
    Sphere left{identity().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75), /*Material{color(1, 0.8, 0.1), 0.1, 0.7, 1, 64}*/ &stripes};

    w.add_object(middle);
    w.add_object(right);
    w.add_object(left);

    PointLight light{color(1, 1, 1), point(-2, 2, -2)};
    PointLight light2{color(1, 1, 1), point(10, 10, -10)};

    w.add_light(light);
    w.add_light(light2);

    Camera c{1000, 500, Constants::PI / 3};
    Tuple from = point(0, 1.5, -5);
    Tuple to = point(0, 1, 0);
    Tuple up = vector(0, 1, 0);
    c.set_transform(view(from, to, up));
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Rendering...\n";
    Framebuffer image = c.render(w);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Finished in " << (std::chrono::duration_cast<std::chrono::seconds>(stop - start)).count() << " seconds\n";
    image.save_buffer("output1.ppm");

    return 1;
}