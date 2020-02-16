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
    return 1;
}