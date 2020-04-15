#ifndef COLOR_H
#define COLOR_H

#include <iostream>

namespace image
{

class Color
{
private:
    // attributes
    double m_rgb[3];

public:
    Color(double r = 0, double g = 0, double b = 0);

    // accessor methods
    double r() const;
    double g() const;
    double b() const;
    
    // arithmetic overloads
    friend Color operator*(const Color &lhs, double rhs);
    friend Color operator/(const Color &lhs, double rhs);
    friend Color operator+(const Color &lhs, const Color &rhs);
    friend Color operator-(const Color &lhs, const Color &rhs);
    friend Color& operator+=(Color &lhs, const Color &rhs);

    // print overload
    friend std::ostream& operator<<(std::ostream &out, const Color &rhs);
};

// utility function
Color hadamard_product(const Color &lhs, const Color &rhs);

} // namespace image

#endif