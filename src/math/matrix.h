#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "utility/common.h"
#include "math/tuple.h"

namespace math
{

// base Matrix class
template <typename T, size_t M, size_t N>
class MatrixBase
{
private:
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

    // matrix arithmetic
    friend MatrixBase<T, M, N> operator*(const MatrixBase<T, M, N> &lhs, const MatrixBase<T, N, M> &rhs);
    friend MatrixBase<T, M, N> operator*(const MatrixBase<T, M, N> &lhs, const Tuple<T, N> &rhs);

    // matrix operations
    MatrixBase<T, N, M> transpose() const;
    virtual double determinant() const;
    MatrixBase<T, M - 1, N - 1> submatrix(const size_t row, const size_t col) const;
    double cofactor(const size_t row, const size_t col) const;
    MatrixBase<T, M, N> inverse() const;

    // print overload
    friend std::ostream& operator<<(std::ostream &out, const MatrixBase &rhs);
};

template <typename T, size_t M, size_t N>
class Matrix : public MatrixBase<T, M, N>
{};

// 2x2 matrix specialization
template <typename T>
class Matrix<T, 2, 2> : public MatrixBase<T, 2, 2>
{
public:
    // matrix operations
    virtual double determinant() const override;
};

// 4x4 matrix specialization
template <typename T> 
class Matrix<T, 4, 4> : public MatrixBase<T, 4, 4>
{
public:
    // transformations
    Matrix<T, 4, 4> translate(T x, T y, T z) const;
    Matrix<T, 4, 4> scale(T x, T y, T z) const;
    Matrix<T, 4, 4> rotate_x(T r) const;
    Matrix<T, 4, 4> rotate_y(T r) const;
    Matrix<T, 4, 4> rotate_z(T r) const;
    Matrix<T, 4, 4> shear(T x_y, T x_z, T y_x, T y_z, T z_x, T z_y) const;
};

// convenience function
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
	    m_buffer[i][j] = 0;
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
	    m_buffer[i][j] = rhs(i, j);
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
	    m_buffer[i][j] = rhs(i, j);
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
    return m_buffer[row][col];
}

template <typename T, size_t M, size_t N>
inline const T& MatrixBase<T, M, N>::operator()(const size_t row, const size_t col) const
{
    assert(row < m_rows && col < m_columns && "index out of bounds");
    return m_buffer[row][col];
}

template <typename T, size_t M, size_t N>
inline MatrixBase<T, M, M> operator*(const MatrixBase<T, M, N> &lhs, const MatrixBase<T, N, M> &rhs)
{
    MatrixBase<T, M, M> ret{};
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
inline Tuple<T, N> operator*(const MatrixBase<T, M, N> &lhs, const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret{};
    for (int i = 0; i < M); i++)
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
inline MatrixBase<T, N, M> MatrixBase<T, M, N>::transpose() const
{
    MatrixBase<T, N, M> ret{};
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    ret(j, i) = m_buffer[i][j];
	}
    }
    return ret;
}

template <typename T, size_t M, size_t N>
double MatrixBase<T, M, N>::determinant() const
{
    assert(m_rows == m_columns && "non-square matrix given");

    double total = 0;
    for (int i = 0; i < N; i++)
    {
	total += cofactor(0, i) * m_buffer[0][i];
    }
    return total;
}

template <typename T, size_t M, size_t N>
MatrixBase<T, M - 1, N - 1> MatrixBase<T, M, N>::submatrix(const size_t row, const size_t col) const
{
    assert(row >= 0 && row < m_rows &&
	   column >= 0 && column < m_columns &&
	   "index out of bounds");

    int x = 0, y = 0;
    MatrixBase<T, M - 1, N - 1> ret{};
    for (int i = 0; i < M; i++)
    {
	if (i == row) continue;
	for (int j = 0; j < N; j++)
	{
	    if (j == column) continue;
	    ret.set(x, y) = m_buffer[i][j];
	    y++;
	}
	y = 0; x++;
    }
    return ret;
}

template <typename T, size_t M, size_t N>
double MatrixBase<T, M, N>::cofactor(const size_t row, const size_t col) const
{
    return submatrix(row, col).determinant() * (((row + col) % 2 == 0) ? 1 : -1);
}

template <typename T, size_t M, size_t N>
MatrixBase<T, M, N> MatrixBase<T, M, N>::inverse() const
{
    double det = determinant();
    assert(det != 0 &&
	"noninvertible matrix");

    MatrixBase<T, M, N> ret{};
    for (int i = 0; i < M; i++)
    {
	for (int j = 0; j < N; j++)
	{
	    ret(i, j) = cofactor(i, j) / det;
	}
    }
    return ret.transpose();
}

template <typename T, size_t M, size_t N>
std::ostream& operator<<(std::ostream &out, const MatrixBase<T, M, N> &rhs)
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

// 2x2 specialization implementation
template <typename T>
inline double Matrix<T, 2, 2>::determinant() const
{
    return m_buffer[0][0] * m_buffer[1][1] - m_buffer[1][0] * m_buffer[0][1];
}

// 4x4 specialization implementation
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
    Tuple<T, 4> forward = normalize(to - from);
    Tuple<T, 4> left = cross(forward, normalize(up));
    Tuple<T, 4> true_up = cross(left, forward);

    Matrix<T, 4, 4> orientation = identity<T, 4>();

    for (int i = 0; i < 3; i++)
    {
	orientiation(0, i) = left(i));
    }

    for (int i = 0; i < 3; i++)
    {
	orientation(1, i) = true_up(i));
    }

    for (int i = 0; i < 3; i++)
    {
	orientation(2, i) = -forward.get(i));
    }

    return orientation * identity<T, 4>().translate(-from(0), -from(1), -from(2)));
}

// specializations
typedef Matrix<int, 2, 2> Matrix2i;
typedef Matrix<float, 2, 2> Matrix2f;
typedef Matrix<double, 2, 2> Matrix2d;

typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<double, 3, 3> Matrix3d;

typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 4, 4> Matrix4d;

} // namespace math

#endif