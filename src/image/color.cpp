#include "image/color.h"

inline image::Color::Color(double r, double g, double b) :
    m_rgb{r, g, b}
{}

// accessor methods
inline double image::Color::r() const
{
    return m_rgb[0];
}

inline double image::Color::g() const
{
    return m_rgb[1];
}

inline double image::Color::b() const
{
    return m_rgb[2];
}

// arithmetic overloads
inline image::Color image::operator*(const image::Color &lhs, double rhs)
{
    return image::Color{lhs.r() * rhs, lhs.g() * rhs, lhs.b() * rhs};
}

inline image::Color image::operator/(const image::Color &lhs, double rhs)
{
    return lhs * (1 / rhs);
}

inline image::Color image::operator+(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r() + rhs.r(), lhs.g() + rhs.g(), lhs.b() + rhs.b()};
}

inline image::Color image::operator-(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r() - rhs.r(), lhs.g() - rhs.g(), lhs.b() - rhs.b()};
}

inline image::Color& image::operator+=(image::Color &lhs, const image::Color &rhs)
{
    lhs.m_rgb[0] += rhs.r();
    lhs.m_rgb[1] += rhs.g();
    lhs.m_rgb[2] += rhs.b();
    return lhs;
}

// print overload
std::ostream& image::operator<<(std::ostream &out, const image::Color &rhs)
{
    for (int i = 0; i < 3; i++)
    {
	if (rhs.m_rgb[i] >= 1)
	    out << 255 << ' ';
	else
	    out << (int) (rhs.m_rgb[i] * 256) << ' ';
    }

    return out;
}

// utility function
inline image::Color image::hadamard_product(const image::Color &lhs, const image::Color &rhs)
{
    return image::Color{lhs.r() * rhs.r(), lhs.g() * rhs.g(), lhs.b() * rhs.b()};
}