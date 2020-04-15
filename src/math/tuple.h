#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "utility/constants.h"

namespace math
{

class Tuple4d
{
private:
    double m_buffer[4];

public:
    Tuple4d();

    // copy overloads
    Tuple4d(const Tuple4d &rhs);
    Tuple4d& operator=(const Tuple4d &rhs);

    // accessor methods
    double& operator()(const size_t idx);
    const double& operator()(const size_t idx) const;

    // arithmetic overloads
    friend Tuple4d operator-(const Tuple4d &rhs);
    friend Tuple4d operator+(const Tuple4d &lhs, const Tuple4d &rhs);
    friend Tuple4d operator-(const Tuple4d &lhs, const Tuple4d &rhs);
    friend Tuple4d operator*(const Tuple4d &lhs, double s);
    friend Tuple4d operator/(const Tuple4d &lhs, double s);
    friend Tuple4d& operator+=(Tuple4d &lhs, const Tuple4d &rhs);

    // tuple logic
    double magnitude() const;
    Tuple4d normalize() const;
};

// utility functions
Tuple4d reflect(const Tuple4d &in, const Tuple4d &normal);
double dot(const Tuple4d &lhs, const Tuple4d &rhs);
Tuple4d cross(const Tuple4d &lhs, const Tuple4d &rhs);

// convenience functions
Tuple4d point(double x, double y, double z);
Tuple4d vector(double x, double y, double z);

} // namespace math

#endif