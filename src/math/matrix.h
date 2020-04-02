#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "utility/common.h"
#include "math/tuple.h"

namespace math
{

template <typename T, size_t M, size_t N>
class Matrix;

// base Matrix class
template <typename T, size_t M, size_t N>
class MatrixBase
{
protected:
    // attributes
    int m_rows = M, m_columns = N;
    T m_buffer[M][N];

public:
    MatrixBase();

    // copy overloads
    MatrixBase(const MatrixBase<T, M, N> &rhs);
    MatrixBase<T, M, N>& operator=(const MatrixBase<T, M, N> &rhs);

    // accessor methods
    int rows() const;
    int columns() const;

    T& operator()(const size_t row, const size_t col);
    const T& operator()(const size_t row, const size_t col) const;

    // utility functions
    Matrix<T, N, M> transpose() const;
};

template <typename T, size_t M, size_t N>
class Matrix : public MatrixBase<T, M, N>
{
public:
    Matrix();

    // copy overloads
    Matrix(const MatrixBase<T, M, N> &rhs);
    Matrix<T, M, N>& operator=(const MatrixBase<T, M, N> &rhs);
};

// 3x3 matrix specialization
template <typename T>
class Matrix<T, 3, 3> : public MatrixBase<T, 3, 3>
{
public:
    Matrix();

    // copy overloads
    Matrix(const MatrixBase<T, 3, 3> &rhs);
    Matrix<T, 3, 3>& operator=(const MatrixBase<T, 3, 3> &rhs);

    // matrix operations
    double determinant() const;
};

// 4x4 matrix specialization
template <typename T> 
class Matrix<T, 4, 4> : public MatrixBase<T, 4, 4>
{
public:
    Matrix();

    // copy overloads
    Matrix(const MatrixBase<T, 4, 4> &rhs);
    Matrix<T, 4, 4>& operator=(const MatrixBase<T, 4, 4> &rhs);

    // matrix operators
    Matrix<T, 3, 3> submatrix(const size_t row, const size_t col) const;
    double cofactor(const size_t row, const size_t col) const;
    double determinant() const;
    Matrix<T, 4, 4> inverse() const;

    // transformations
    Matrix<T, 4, 4> translate(T x, T y, T z) const;
    Matrix<T, 4, 4> scale(T x, T y, T z) const;
    Matrix<T, 4, 4> rotate_x(T r) const;
    Matrix<T, 4, 4> rotate_y(T r) const;
    Matrix<T, 4, 4> rotate_z(T r) const;
    Matrix<T, 4, 4> shear(T x_y, T x_z, T y_x, T y_z, T z_x, T z_y) const;
};

// matrix arithmetic
template <typename T, size_t M, size_t N> Matrix<T, M, M> operator*(const Matrix<T, M, N> &lhs, const Matrix<T, M, N> &rhs);
template <typename T, size_t M, size_t N> Tuple<T, N> operator*(const Matrix<T, M, N> &lhs, const Tuple<T, N> &rhs);

// print overload
template <typename T, size_t M, size_t N> std::ostream& operator<<(std::ostream &out, const Matrix<T, M, N> &rhs);

// convenience functions
template <typename T, size_t N> Matrix<T, N, N> identity();
template <typename T> Matrix<T, 4, 4> view(const Tuple<T, 4> &from, const Tuple<T, 4> &to, const Tuple<T, 4> &up);

// implementation
template <typename T, size_t M, size_t N>
inline MatrixBase<T, M, N>::MatrixBase()
{
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    this->m_buffer[i][j] = 0;
	}
    }
}

template <typename T, size_t M, size_t N>
inline MatrixBase<T, M, N>::MatrixBase(const MatrixBase &rhs)
{
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
}

template <typename T, size_t M, size_t N>
inline MatrixBase<T, M, N>& MatrixBase<T, M, N>::operator=(const MatrixBase &rhs)
{
    if (&rhs == this)
	return *this;

    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }

    return *this;
}

template <typename T, size_t M, size_t N>
inline int MatrixBase<T, M, N>::rows() const
{
    return m_rows;
}

template <typename T, size_t M, size_t N>
inline int MatrixBase<T, M, N>::columns() const
{
    return m_columns;
}

template <typename T, size_t M, size_t N>
inline T& MatrixBase<T, M, N>::operator()(const size_t row, const size_t col)
{
    assert(row < m_rows && col < m_columns && "index out of bounds");
    return this->m_buffer[row][col];
}

template <typename T, size_t M, size_t N>
inline const T& MatrixBase<T, M, N>::operator()(const size_t row, const size_t col) const
{
    assert(row < m_rows && col < m_columns && "index out of bounds");
    return this->m_buffer[row][col];
}

template <typename T, size_t M, size_t N>
inline Matrix<T, N, M> MatrixBase<T, M, N>::transpose() const
{
    Matrix<T, N, M> ret{};
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    ret(j, i) = this->m_buffer[i][j];
	}
    }
    return ret;
}

template <typename T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix() :
    MatrixBase<T, M, N>{}
{}

template <typename T, size_t M, size_t N>
inline Matrix<T, M, N>::Matrix(const MatrixBase<T, M, N> &rhs)
{
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
}

template <typename T, size_t M, size_t N>
inline Matrix<T, M, N>& Matrix<T, M, N>::operator=(const MatrixBase<T, M, N> &rhs)
{
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
    return *this;
}

// 3x3 specialization implementation
template <typename T>
inline Matrix<T, 3, 3>::Matrix() :
    MatrixBase<T, 3, 3>{}
{}

template <typename T>
inline Matrix<T, 3, 3>::Matrix(const MatrixBase<T, 3, 3> &rhs)
{
    for (int i = 0; i < 3; i++)
    {
	for (int j = 0; j < 3; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
}

template <typename T>
inline Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator=(const MatrixBase<T, 3, 3> &rhs)
{
    for (int i = 0; i < 3; i++)
    {
	for (int j = 0; j < 3; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
    return *this;
}

template <typename T>
inline double Matrix<T, 3, 3>::determinant() const
{
    return (this->m_buffer[0][0] * this->m_buffer[1][1] * this->m_buffer[2][2] +
	    this->m_buffer[0][1] * this->m_buffer[1][2] * this->m_buffer[2][0] +
	    this->m_buffer[0][2] * this->m_buffer[1][0] * this->m_buffer[2][1] -
	    this->m_buffer[0][2] * this->m_buffer[1][1] * this->m_buffer[2][0] -
	    this->m_buffer[0][1] * this->m_buffer[1][0] * this->m_buffer[2][2] -
	    this->m_buffer[0][0] * this->m_buffer[1][2] * this->m_buffer[2][1]);
}

// 4x4 specialization implementation
template <typename T>
inline Matrix<T, 4, 4>::Matrix() :
    MatrixBase<T, 4, 4>{}
{}

template <typename T>
inline Matrix<T, 4, 4>::Matrix(const MatrixBase<T, 4, 4> &rhs)
{
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
}

template <typename T>
inline Matrix<T, 4, 4>& Matrix<T, 4, 4>::operator=(const MatrixBase<T, 4, 4> &rhs)
{
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    this->m_buffer[i][j] = rhs(i, j);
	}
    }
    return *this;
}

template <typename T>
Matrix<T, 3, 3> Matrix<T, 4, 4>::submatrix(const size_t row, const size_t col) const
{
    assert(row >= 0 && row < this->m_rows &&
	   col >= 0 && col < this->m_columns &&
	   "index out of bounds");

    int x = 0, y = 0;
    Matrix<T, 3, 3> ret{};
    for (int i = 0; i < 4; i++)
    {
	if (i == row) continue;
	for (int j = 0; j < 4; j++)
	{
	    if (j == col) continue;
	    ret(x, y) = this->m_buffer[i][j];
	    y++;
	}
	y = 0; x++;
    }
    return ret;
}

template <typename T>
double Matrix<T, 4, 4>::cofactor(const size_t row, const size_t col) const
{
    return submatrix(row, col).determinant() * (((row + col) % 2 == 0) ? 1 : -1);
}

template <typename T>
double Matrix<T, 4, 4>::determinant() const
{
    double total = 0;
    for (int i = 0; i < 4; i++)
    {
	total += cofactor(0, i) * this->m_buffer[0][i];
    }
    return total;
}

template <typename T>
Matrix<T, 4, 4> Matrix<T, 4, 4>::inverse() const
{
    double det = determinant();
    assert(det != 0 &&
	"noninvertible matrix");

    Matrix<T, 4, 4> ret{};
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    ret(i, j) = cofactor(i, j) / det;
	}
    }
    return ret.transpose();
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::translate(T x, T y, T z) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(0, 3) = x;
    ret(1, 3) = y;
    ret(2, 3) = z;
    return ret * (*this);
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::scale(T x, T y, T z) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(0, 0) = x;
    ret(1, 1) = y;
    ret(2, 2) = z;
    return ret * (*this);
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::rotate_x(T r) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(1, 1) = std::cos(r);
    ret(1, 2) = - std::sin(r);
    ret(2, 1) = std::sin(r);
    ret(2, 2) = std::cos(r);
    return ret * (*this);
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::rotate_y(T r) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(0, 0) = std::cos(r);
    ret(0, 2) = std::sin(r);
    ret(2, 0) = -std::sin(r);
    ret(2, 2) = std::cos(r);
    return ret * (*this);
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::rotate_z(T r) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(0, 0) = std::cos(r);
    ret(0, 1) = -std::sin(r);
    ret(1, 0) = std::sin(r);
    ret(1, 1) = std::cos(r);
    return ret * (*this);
}

template <typename T>
inline Matrix<T, 4, 4> Matrix<T, 4, 4>::shear(T x_y, T x_z, T y_x, T y_z, T z_x, T z_y) const
{
    Matrix<T, 4, 4> ret = identity<T, 4>();
    ret(0, 1) = x_y;
    ret(0, 2) = x_z;
    ret(1, 0) = y_x;
    ret(1, 2) = y_z;
    ret(2, 0) = z_x;
    ret(2, 1) = z_y;
    return ret * (*this);
}

template <typename T, size_t M, size_t N>
inline Matrix<T, M, M> operator*(const Matrix<T, M, N> &lhs, const Matrix<T, M, N> &rhs)
{
    Matrix<T, M, N> ret{};
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < M; j++)
	{
	    double total = 0;
	    for (int k = 0; k < N; k++)
	    {
		total += lhs(i, k) * rhs(k, j);
	    }
	    ret(i, j) = total;
	}
    }
    return ret;
}

template <typename T, size_t M, size_t N>
inline Tuple<T, N> operator*(const Matrix<T, M, N> &lhs, const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret{};
    for (int i = 0; i < M; i++)
    {
	double total = 0;
	for (int j = 0; j < N; j++)
	{
	    total += lhs(i, j) * rhs(j);
	}
	ret(i) = total;
    }
    return ret;
}

template <typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream &out, const Matrix<T, M, N> &rhs)
{
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    out << rhs(i, j) << ' ';
	}
	out << '\n';
    }
    return out;
}

template <typename T, size_t N> 
inline Matrix<T, N, N> identity()
{
    Matrix<T, N, N> ret{};
    for (int i = 0; i < N; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    if (i == j)
		ret(i, j) = 1;
	}
    }
    return ret;
}

template <typename T> 
Matrix<T, 4, 4> view(const Tuple<T, 4> &from, const Tuple<T, 4> &to, const Tuple<T, 4> &up)
{
    Tuple<T, 4> forward = (to - from).normalize();
    Tuple<T, 4> left = cross<T>(forward, up.normalize());
    Tuple<T, 4> true_up = cross<T>(left, forward);

    Matrix<T, 4, 4> orientation = identity<T, 4>();

    for (int i = 0; i < 3; i++)
    {
	orientation(0, i) = left(i);
    }

    for (int i = 0; i < 3; i++)
    {
	orientation(1, i) = true_up(i);
    }

    for (int i = 0; i < 3; i++)
    {
	orientation(2, i) = -forward(i);
    }

    return orientation * identity<T, 4>().translate(-from(0), -from(1), -from(2));
}

// specializations
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<double, 3, 3> Matrix3d;

typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 4, 4> Matrix4d;

} // namespace math

#endif