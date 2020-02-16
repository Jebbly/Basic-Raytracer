#include <iostream>
#include "util/common.h"
#include "util/math/tuple.h"
#include "util/math/matrix.h"
#include "util/image/framebuffer.h"

int main()
{
    Matrix m{ 4, 4 };
    m.set(0, 0, 8);
    m.set(0, 1, -5);
    m.set(0, 2, 9);
    m.set(0, 3, 2);
    m.set(1, 0, 7);
    m.set(1, 1, 5);
    m.set(1, 2, 6);
    m.set(1, 3, 1);
    m.set(2, 0, -6);
    m.set(2, 1, 0);
    m.set(2, 2, 9);
    m.set(2, 3, 6);
    m.set(3, 0, -3);
    m.set(3, 1, 0);
    m.set(3, 2, -9);
    m.set(3, 3, -4);
    std::cout << m;
    std::cout << m.inverse();
    std::cout << multiply(m, m.inverse());

    Tuple p = point(3.0, 4.0, 5.0);
    Tuple v = vector(7.0, 5.0, 2.0);
    std::cout << p << "\n";
    std::cout << p + v << "\n";
    std::cout << -p << "\n";
    std::cout << p - v << "\n";
    std::cout << v << "\n";
    std::cout << magnitude(v) << "\n";
    std::cout << normalize(v) << "\n";

    Framebuffer c{100, 100};
    Tuple white = color(255.0, 255.0, 255.0);
    for (double x = 0; x < 100; x++)
    {
	for (double y = 0; y < 100; y++)
	{
	    Tuple col = color(2 * x, 2 * y, 255);
	    c.write_pixel(x, y, col);
	}
    }
    c.save_buffer("output.ppm");
    return 1;
}