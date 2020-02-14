#include <iostream>
#include "util/common.h"
#include "util/math/tuple.h"

int main()
{
    Tuple p = point(3.0, 4.0, 5.0);
    Tuple v = vector(7.0, 5.0, 2.0);
    std::cout << p << "\n";
    std::cout << p + v << "\n";
    std::cout << -p << "\n";
    std::cout << p - v << "\n";
    std::cout << v << "\n";
    std::cout << magnitude(v) << "\n";
    std::cout << normalize(v) << "\n";
    return 1;
}