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

    for (int y = 0; y < 100; y++)
    {
	double world_y = half - (y * pixel_size);
	for (int x = 0; x < 100; x++)
	{
	    double world_x = -half + (x * pixel_size);
	    Tuple position = point(world_x, world_y, wall_z);
	    Ray shoot_ray{ray_origin, normalize(position - ray_origin)};
	    std::vector<Intersection> intersects = intersections(shoot_ray, sph);

	    auto i = hit(intersects);
	    if (i)
	    {
		Tuple col = color(i.value().t() * 100, i.value().t() * 100, i.value().t() * 100);
		canvas.write_pixel(x, y, col);
	    }
	}
    }

    canvas.save_buffer("circle.ppm");
    return 1;
}