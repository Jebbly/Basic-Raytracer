#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "core/intersection.h"
#include "scene/lighting.h"

int main()
{
    Tuple ray_origin = point(0, 0, -5);
    double wall_z = 10;
    double wall_size = 7;

    Framebuffer canvas{100, 100};
    double pixel_size = 7.0 / canvas.get_height();
    double half = wall_size / 2;

    Sphere sph;
    Material m{};
    m.set_shininess(200);
    m.set_color(color(1, 0.2, 1));
    sph.set_material(m);
    PointLight light{color(1, 1, 1), point(-10, 10, -10)};

    std::cout << "Starting...\n";
    for (int y = 0; y < canvas.get_height(); y++)
    {
	double world_y = half - (y * pixel_size);
	for (int x = 0; x < canvas.get_width(); x++)
	{
	    double world_x = -half + (x * pixel_size);
	    Tuple position = point(world_x, world_y, wall_z);
	    Ray shoot_ray{ray_origin, normalize(position - ray_origin)};
	    std::vector<Intersection> intersects = intersections(shoot_ray, sph);

	    auto i = hit(intersects);
	    if (i)
	    {
		Tuple point = shoot_ray.position(i.value().get_t());
		Tuple normal = i.value().get_object().normal(point);
		Tuple eye = -shoot_ray.get_direction();
		Tuple col = lighting(i.value().get_object().get_material(), light, point, eye, normal) * 255;
		canvas.write_pixel(x, y, col);
	    }
	    else
		canvas.write_pixel(x, y, color(0, 0, 0));
	}
    }
    std::cout << "Raytracing Finished - Saving Image...\n";
    canvas.save_buffer("circle.ppm");
    return 1;
}