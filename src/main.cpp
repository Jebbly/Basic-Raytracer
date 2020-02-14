#include <iostream>
#include "util/common.h"
#include "util/math/tuple.h"
#include "util/image/framebuffer.h"

int main()
{
    Framebuffer c{100, 100};
    Tuple white = vector(255.0, 255.0, 255.0);
    for (int x = 0; x < 100; x++)
    {
	for (int y = 0; y < 100; y++)
	{
	    Tuple color = vector(2 * x, 2 * y, 255);
	    c.write_pixel(x, y, color);
	}
    }
    c.save_buffer("output.ppm");
    return 1;
}