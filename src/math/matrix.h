#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include <cmath>
#include <iostream>
#include "utility/constants.h"
#include "math/tuple.h"

namespace math
{

class Matrix4d
{
private:
    // attributes
    double m_buffer[4][4];

public:
    Matrix4d();

    // copy overloads
    Matrix4d(const Matrix4d &rhs);
    Matrix4d& operator=(const Matrix4d &rhs);

    // accessor methods
    double& operator()(const size_t row, const size_t col);
    const double& operator()(const size_t row, const size_t col) const;

    // transformations
    Matrix4d translate(double x, double y, double z) const;
    Matrix4d scale(double x, double y, double z) const;
    Matrix4d rotate_x(double r) const;
    Matrix4d rotate_y(double r) const;
    Matrix4d rotate_z(double r) const;
    Matrix4d shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) const;

    // utility functions
    Matrix4d inverse() const;
    Matrix4d transpose() const;
};

// arithmetic overloads
Matrix4d operator*(const Matrix4d &lhs, double rhs);
Matrix4d operator/(const Matrix4d &lhs, double rhs);
Matrix4d operator*(const Matrix4d &lhs, const Matrix4d &rhs);
Tuple4d operator*(const Matrix4d &lhs, const Tuple4d &rhs);

// convenience functions
Matrix4d identity();
Matrix4d view(const Tuple4d &from, const Tuple4d &to, const Tuple4d &up);

} // namespace math

#endif