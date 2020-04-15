#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <iostream>

namespace image
{

class Color
{
public:
    // attributes
    double r, g, b;

    Color(double red = 0, double green = 0, double blue = 0);
};

// arithmetic overloads
Color operator*(const Color &lhs, double rhs);
Color operator/(const Color &lhs, double rhs);
Color operator+(const Color &lhs, const Color &rhs);
Color operator-(const Color &lhs, const Color &rhs);
Color& operator+=(Color &lhs, const Color &rhs);

// print overload
std::ostream& operator<<(std::ostream &out, const Color &rhs);

// utility function
Color hadamard_product(const Color &lhs, const Color &rhs);

} // namespace image

#endif