#include <iostream>
#include <chrono>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "geometry/primitives/sphere.h"
#include "geometry/primitives/cube.h"
#include "geometry/primitives/cylinder.h"
#include "geometry/primitives/cone.h"
#include "geometry/primitives/plane.h"
#include "geometry/mesh.h"
#include "geometry/group.h"
#include "geometry/primitives/triangle.h"
#include "geometry/csg.h"
#include "geometry/primitives/smooth_triangle.h"
#include "materials/color_material.h"
#include "materials/patterns/stripe_material.h"
#include "materials/patterns/gradient_material.h"
#include "materials/patterns/ring_material.h"
#include "materials/patterns/checker_material.h"
#include "core/intersection.h"
#include "scene/lights/light.h"
#include "scene/lights/point_light.h"
#include "scene/lights/directional_light.h"
#include "scene/lights/spot_light.h"
#include "scene/world.h"
#include "image/camera.h"

int main()
{
    scene::World w{};

    material::pattern::StripeMaterial stripes{math::color<double>(215 / 255.0, 178 / 255.0, 255 / 255.0), math::color<double>(147 / 255.0, 216 / 255.0, 148 / 255.0), math::identity<double, 4>().scale(0.5, 0.5, 0.5), 0.1, 0.9, 1, 200};
    material::pattern::GradientMaterial gradient{math::color<double>(0.8, 0, 0), math::color<double>(0, 0, 0.8), math::identity<double, 4>().scale(1.5, 1.5, 1.5).rotate_y(constants::PI / 3), 0.1, 0.9, 1, 200};
    material::pattern::RingMaterial ring{math::color<double>(211 / 255.0, 217 / 255.0, 231 / 255.0), math::color<double>(141 / 255.0, 153 / 255.0, 186 / 255.0), math::identity<double, 4>().scale(0.25, 0.25, 0.25).rotate_x(constants::PI / 1.5).rotate_y(-constants::PI / 12)};
    material::pattern::CheckerMaterial grid{math::color<double>(0.2, 0.2, 0.2), math::color<double>(0.7, 0.7, 0.7), math::identity<double, 4>(), 0.1, 0.9, 0.9, 200, 1};
    material::ColorMaterial glass{math::color<double>(1, 1, 1), 0, 0, 0.9, 200, 1.0, 1.0, 1.52};
    material::ColorMaterial air{math::color<double>(1, 1, 1), 0, 0, 0.9, 200, 1.0, 1.0, 1.0};
    geometry::primitive::Plane floor{math::identity<double, 4>(), std::make_shared<material::pattern::CheckerMaterial>(grid)};

    // w.add_object(floor);

    geometry::primitive::Sphere middle{math::identity<double, 4>().translate(-0.5, 1, 0.5), /*Material{math::color<double>(0.1, 1, 0.5), 0.1, 0.7, 1, 200}*/ std::make_shared<material::pattern::GradientMaterial>(gradient)};
    geometry::primitive::Cone right{math::identity<double, 4>()./*scale(0.3, 0.5, 0.3).*/translate(1.2, 0, -0.5), /*Material{math::color<double>(0.5, 1, 0.1), 0.1, 0.7, 1, 32}*/ std::make_shared<material::pattern::RingMaterial>(ring), 0, 1, true};
    geometry::primitive::Cylinder left{math::identity<double, 4>().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -1.5).rotate_y(constants::PI / 4), /*Material{math::color<double>(1, 0.8, 0.1), 0.1, 0.7, 1, 64}*/ std::make_shared<material::pattern::StripeMaterial>(stripes), 0, 1, true};
    geometry::Group g{};

    g.add_child(&right);
    g.add_child(&left);
    g.add_child(&middle);

    // Mesh mesh{"astronaut.obj", math::identity<double, 4>().scale(0.05, 0.05, 0.05).rotate_y(constants::PI / 4).translate(0.7, 2.7, 0.2)};

    // Mesh test{"test.obj", math::identity<double, 4>()};
    // w.add_object(test);

    geometry::primitive::Sphere s{math::identity<double, 4>().scale(1.4, 1.4, 1.4).translate(0, 2, 0)};
    geometry::primitive::Cube cy{math::identity<double, 4>().rotate_x(constants::PI / 2).rotate_y(constants::PI / 4).translate(0, 2, 0)};
    geometry::CSG cs{&s, &cy, &geometry::csg_difference};
    w.add_object(cs);

    // w.add_object(middle);
    // w.add_object(right);
    // w.add_object(left);
   // w.add_object(g);
    // w.add_object(mesh);

    // w.add_object(mainSphere);
    // w.add_object(mainSphere2);

    scene::light::PointLight light{math::color<double>(1, 1, 1), math::point<double>(-5, 5, -5)};
    scene::light::PointLight light2{math::color<double>(1, 1, 1), math::point<double>(10, 10, -10)};

    w.add_light(light);
    w.add_light(light2);

    image::Camera c{256, 144, constants::PI / 3};
    math::Tuple4d from = math::point<double>(0, 3, -9);
    math::Tuple4d to = math::point<double>(0, 2, 0);
    math::Tuple4d up = math::vector<double>(0, 1, 0);
    c.set_transform(math::view(from, to, up));
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Rendering...\n";
    image::Framebuffer image = c.render(w);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Finished in " << (std::chrono::duration_cast<std::chrono::seconds>(stop - start)).count() << " seconds\n";
    image.save_buffer("teapot.ppm");
    return 0;
}

