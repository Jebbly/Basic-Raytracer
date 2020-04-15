#include "math/tuple.h"

math::Tuple4d::Tuple4d()
{
    for (int i = 0; i < 4; i++)
    {
	this->m_buffer[i] = 0;
    }
}

// copy overloads
math::Tuple4d::Tuple4d(const math::Tuple4d &rhs)
{
    for (int i = 0; i < 4; i++)
    {
	this->m_buffer[i] = rhs(i);
    }
}

math::Tuple4d& math::Tuple4d::operator=(const math::Tuple4d &rhs)
{
    if (&rhs == this)
	return *this;

    for (int i = 0; i < 4; i++)
    {
	this->m_buffer[i] = rhs(i);
    }

    return *this;
}

// accessor methods
inline double& math::Tuple4d::operator()(const size_t idx)
{
    assert(idx < 4 && "index out of bounds");
    return this->m_buffer[idx];
}

inline const double& math::Tuple4d::operator()(const size_t idx) const
{
    assert(idx < 4 && "index out of bounds");
    return this->m_buffer[idx];
}

// arithmetic overloads
inline math::Tuple4d math::operator-(const math::Tuple4d &rhs)
{
    math::Tuple4d ret;
    for (int i = 0; i < 4; i++)
    {
	ret(i) = -rhs(i);
    }
    return ret;
}

inline math::Tuple4d math::operator+(const math::Tuple4d &lhs, const math::Tuple4d &rhs)
{
    math::Tuple4d ret;
    for (int i = 0; i < 4; i++)
    {
	ret(i) = lhs(i) + rhs(i);
    }
    return ret;
}

inline math::Tuple4d math::operator-(const math::Tuple4d &lhs, const math::Tuple4d &rhs)
{
    math::Tuple4d ret;
    for (int i = 0; i < 4; i++)
    {
	ret(i) = lhs(i) - rhs(i);
    }
    return ret;
}

inline math::Tuple4d math::operator*(const math::Tuple4d &lhs, double s)
{
    math::Tuple4d ret;
    for (int i = 0; i < 4; i++)
    {
	ret(i) = lhs(i) * s;
    }
    return ret;
}

inline math::Tuple4d math::operator/(const math::Tuple4d &lhs, double s)
{
    return lhs * (1 / s);
}


inline math::Tuple4d& math::operator+=(math::Tuple4d &lhs, const math::Tuple4d &rhs)
{
    for (int i = 0; i < 4; i++)
    {
	lhs(i) += rhs(i);
    }

    return lhs;
}

// tuple logic
inline double math::Tuple4d::magnitude() const
{
    double total = 0;
    for (int i = 0; i < 4; i++)
    {
	total += pow(this->m_buffer[i], 2);
    }
    return sqrt(total);
}

inline math::Tuple4d math::Tuple4d::normalize() const
{
    double scalar = magnitude();

    math::Tuple4d ret{};
    for (int i = 0; i < 4; i++)
    {
	ret(i) = this->m_buffer[i] / scalar;
    }
    return ret;
}

// utility functions
inline math::Tuple4d math::reflect(const math::Tuple4d &in, const math::Tuple4d &normal)
{
    return in - normal * 2 * dot(in, normal);
}

inline double math::dot(const math::Tuple4d &lhs, const math::Tuple4d &rhs)
{
    double total = 0;
    for (int i = 0; i < 4; i++)
    {
	total += lhs(i) * rhs(i);
    }
    return total;
}

inline math::Tuple4d math::cross(const math::Tuple4d &lhs, const math::Tuple4d &rhs)
{
    return vector(lhs(1) * rhs(2) - lhs(2) * rhs(1),
		  lhs(2) * rhs(0) - lhs(0) * rhs(2),
		  lhs(0) * rhs(1) - lhs(1) * rhs(0));
}

// convenience functions
inline math::Tuple4d math::point(double x, double y, double z)
{
    math::Tuple4d ret;
    ret(0) = x;
    ret(1) = y;
    ret(2) = z;
    ret(3) = 1;
    return ret;
}

inline math::Tuple4d math::vector(double x, double y, double z)
{
    math::Tuple4d ret;
    ret(0) = x;
    ret(1) = y;
    ret(2) = z;
    ret(3) = 0;
    return ret;
}