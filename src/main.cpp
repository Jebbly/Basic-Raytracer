#include <chrono>
#include <iostream>
#include <memory>
#include "math/tuple.h"
#include "math/matrix.h"
#include "image/camera.h"
#include "image/framebuffer.h"
#include "geometry/group.h"
#include "geometry/primitives/cylinder.h"
#include "geometry/primitives/sphere.h"
#include "geometry/primitives/plane.h"
#include "material/color_material.h"
#include "material/patterns/checker_material.h"
#include "material/patterns/gradient_material.h"
#include "material/patterns/ring_material.h"
#include "material/patterns/stripe_material.h"
#include "scene/lights/light.h"
#include "scene/lights/point_light.h"
#include "scene/world.h"

// example render
int main()
{
    // create world
    scene::World world{};

    // setup materials
    material::pattern::StripeMaterial stripes{image::Color{215 / 255.0, 178 / 255.0, 255 / 255.0}, image::Color{147 / 255.0, 216 / 255.0, 148 / 255.0}, math::identity().scale(0.5, 0.5, 0.5), 0.1, 0.9, 1, 200};
    material::pattern::GradientMaterial gradient{image::Color{0.8, 0, 0}, image::Color{0, 0, 0.8}, math::identity().scale(1.5, 1.5, 1.5).rotate_y(constants::PI / 3), 0.1, 0.9, 1, 200};
    material::pattern::RingMaterial ring{image::Color{211 / 255.0, 217 / 255.0, 231 / 255.0}, image::Color{141 / 255.0, 153 / 255.0, 186 / 255.0}, math::identity().scale(0.25, 0.25, 0.25).rotate_x(constants::PI / 1.5).rotate_y(-constants::PI / 12)};
    material::pattern::CheckerMaterial grid{image::Color{0.2, 0.2, 0.2}, image::Color{0.7, 0.7, 0.7}, math::identity(), 0.1, 0.9, 0.9, 200, 1};

    // create objects with materials
    geometry::primitive::Plane floor{math::identity(), std::make_shared<material::pattern::CheckerMaterial>(grid)};
    geometry::primitive::Sphere middle{math::identity().translate(-0.5, 1, 0.5), std::make_shared<material::pattern::GradientMaterial>(gradient)};
    geometry::primitive::Sphere right{math::identity().scale(0.5, 0.5, 0.5).translate(1.2, 0.5, -0.5), std::make_shared<material::pattern::RingMaterial>(ring)};
    geometry::primitive::Sphere left{math::identity().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -1.5).rotate_y(constants::PI / 4), std::make_shared<material::pattern::StripeMaterial>(stripes)};
    
    // group spheres together
    geometry::Group spheres{};
    spheres.add_child(&right);
    spheres.add_child(&left);
    spheres.add_child(&middle);

    // add objects to scene
    world.add_object(floor);
    world.add_object(spheres);

    // create lights
    scene::light::PointLight key{image::Color{1, 1, 1}, math::point(-5, 5, -5)};
    scene::light::PointLight fill{image::Color{1, 1, 1}, math::point(10, 10, -10)};

    // add lights to scene
    world.add_light(key);
    world.add_light(fill);

    // configure camera
    image::Camera camera{1600, 800, constants::PI / 3};
    math::Tuple4d from = math::point(0, 1.5, -5);
    math::Tuple4d to = math::point(0, 1, 0);
    math::Tuple4d up = math::vector(0, 1, 0);
    camera.transform(math::view(from, to, up));

    // render scene to buffer
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Rendering image...\n";
    image::Framebuffer image = camera.render(world);
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Finished in " << (std::chrono::duration_cast<std::chrono::seconds>(stop - start)).count() << " seconds!\n";

    // write buffer to file
    image.save_buffer("example.ppm");
    std::cout << "Press any key to exit.\n";

    return 0;
}

