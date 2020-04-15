#include "image/color.h"

image::Color::Color(double r, double g, double b) :
    r{r},
    g{g},
    b{b}
{}

// arithmetic overloads
image::Color image::operator*(const image::Color &lhs, double rhs)
{
    return image::Color{lhs.r * rhs, lhs.g * rhs, lhs.b * rhs};
}

image::Color image::operator/(const image::Color &lhs, double rhs)
{
    return lhs * (1 / rhs);
}

image::Color image::operator+(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b};
}

image::Color image::operator-(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b};
}

image::Color& image::operator+=(image::Color &lhs, const image::Color &rhs)
{
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    return lhs;
}

// print overload
std::ostream& image::operator<<(std::ostream &out, const image::Color &rhs)
{
    out << std::clamp((int) (rhs.r * 256), 0, 255) << ' ';
    out << std::clamp((int) (rhs.g * 256), 0, 255) << ' ';
    out << std::clamp((int) (rhs.b * 256), 0, 255) << ' ';

    return out;
}

// utility function
image::Color image::hadamard_product(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b};
}
