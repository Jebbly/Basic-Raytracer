#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"

int main()
{
    Matrix transform = identity().rotate_x(PI / 2).scale(5, 5, 5).translate(10, 5, 7);
    Tuple p = point(2.0, 3.0, 4.0);
    Tuple v = vector(1.0, 0.0, 0.0);
    Ray r{p, v};
    for (int i = -1; i < 2; i++)
	std::cout << "P: " << r.position(i) << "\n";
    std::cout << "P: " << r.position(2.5) << "\n";
    std::cout << p;

    // Framebuffer c{101, 101};
    /*Tuple dot = point(0.0, 0.0, 1.0);
    Tuple white = color(255.0, 255.0, 255.0);
    for (double i = 0; i < 12; i++)
    {
	Matrix rotation = identity().rotate_y(i * PI / 6).scale(25, 25, 25);
	Tuple end = multiply(rotation, dot);
	c.write_pixel(end.get(0) + 50, end.get(2) + 50, white);
    }
    c.save_buffer("output.ppm");*/
    return 1;
}