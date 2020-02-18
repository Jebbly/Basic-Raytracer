#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "image/framebuffer.h"

int main()
{
    Matrix transform = identity().rotate_x(PI / 2).scale(5, 5, 5).translate(10, 5, 7);
    Tuple p1 = point(1.0, 0.0, 1.0);
    std::cout << "P: " << multiply(transform, p1) << "\n";

    Framebuffer c{101, 101};
    Tuple dot = point(0.0, 0.0, 1.0);
    for (double i = 0; i < 12; i++)
    {
	Matrix rotation = identity().rotate_y(i * PI / 6).scale(25, 25, 25);
	Tuple white = color(255.0, 255.0, 255.0);
	Tuple end = multiply(rotation, dot);
	c.write_pixel(end.get(0) + 50, end.get(2) + 50, white);
    }
    c.save_buffer("output.ppm");
    return 1;
}