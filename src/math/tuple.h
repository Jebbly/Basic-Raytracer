#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "utility/common.h"

namespace math
{

template <typename T, size_t N>
class Tuple;

// base Tuple class
template <typename T, size_t N>
class TupleBase
{
protected:
    // attributes
    int m_size = N;
    T m_buffer[N];

public:
    TupleBase();

    // copy overloads
    TupleBase(const TupleBase<T, N> &rhs);
    TupleBase<T, N>& operator=(const TupleBase<T, N> &rhs);

    // accessor methods
    int size() const;

    T& operator()(const size_t idx);
    const T& operator()(const size_t idx) const;

    // utility functions
    double magnitude() const;
    Tuple<T, N> normalize() const;
};

template <typename T, size_t N>
class Tuple : public TupleBase<T, N>
{
public:
    Tuple();
    
    // copy overloads
    Tuple(const TupleBase<T, N> &rhs);
    Tuple<T, N>& operator=(const TupleBase<T, N> &rhs);
};

// arithmetic overloads
template <typename T, size_t N> Tuple<T, N> operator-(const Tuple<T, N> &rhs);
template <typename T, size_t N> Tuple<T, N> operator+(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs);
template <typename T, size_t N> Tuple<T, N> operator-(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs);
template <typename T, size_t N> Tuple<T, N> operator*(const Tuple<T, N> &lhs, double s);
template <typename T, size_t N> Tuple<T, N> operator/(const Tuple<T, N> &lhs, double s);
template <typename T, size_t N> Tuple<T, N>& operator+=(Tuple<T, N> &lhs, const Tuple<T, N> &rhs);

// print overload
template <typename T, size_t N> std::ostream& operator<<(std::ostream &out, const Tuple<T, N> &rhs);

// utility functions
template <typename T> Tuple<T, 4> reflect(const Tuple<T, 4> &in, const Tuple<T, 4> &normal);
template <typename T, size_t N> double dot(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs);
template <typename T> Tuple<T, 4> cross(const Tuple<T, 4> &lhs, const Tuple<T, 4> &rhs);
template <typename T, size_t N> Tuple<T, N> hadamard_product(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs);

// convenience functions
template <typename T> Tuple<T, 4> point(T x, T y, T z);
template <typename T> Tuple<T, 4> vector(T x, T y, T z);
template <typename T> Tuple<T, 3> color(T r, T g, T b);

// implementation
template <typename T, size_t N>
inline TupleBase<T, N>::TupleBase()
{
    for (int i = 0; i < N; i++)
    {
	this->m_buffer[i] = 0;
    }
}

template <typename T, size_t N>
inline TupleBase<T, N>::TupleBase(const TupleBase<T, N> &rhs)
{
    for (int i = 0; i < N; i++)
    {
	this->m_buffer[i] = rhs(i);
    }
}

template <typename T, size_t N>
inline TupleBase<T, N>& TupleBase<T, N>::operator=(const TupleBase<T, N> &rhs)
{
    if (&rhs == this)
	return *this;

    for (int i = 0; i < N; i++)
    {
	this->m_buffer[i] = rhs(i);
    }

    return *this;
}

template <typename T, size_t N>
inline int TupleBase<T, N>::size() const
{
    return m_size;
}

template <typename T, size_t N>
inline T& TupleBase<T, N>::operator()(const size_t idx)
{
    assert(idx < m_size && "index out of bounds");
    return this->m_buffer[idx];
}

template <typename T, size_t N>
inline const T& TupleBase<T, N>::operator()(const size_t idx) const
{
    assert(idx < m_size && "index out of bounds");
    return this->m_buffer[idx];
}

template <typename T, size_t N>
inline double TupleBase<T, N>::magnitude() const
{
    double total = 0;
    for (int i = 0; i < N; i++)
    {
	total += pow(this->m_buffer[i], 2);
    }
    return sqrt(total);
}

template <typename T, size_t N>
inline Tuple<T, N> TupleBase<T, N>::normalize() const
{
    double scalar = magnitude();
    Tuple<T, N> ret{};
    for (int i = 0; i < N; i++)
    {
	ret(i) = this->m_buffer[i] / scalar;
    }
    return ret;
}

template <typename T, size_t N>
inline Tuple<T, N>::Tuple() :
    TupleBase<T, N>{}
{}

template <typename T, size_t N>
inline Tuple<T, N>::Tuple(const TupleBase<T, N> &rhs)
{
    for (int i = 0; i < N; i++)
    {
	this->m_buffer[i] = rhs(i);
    }
}

template <typename T, size_t N>
inline Tuple<T, N>& Tuple<T, N>::operator=(const TupleBase<T, N> &rhs)
{
    for (int i = 0; i < N; i++)
    {
	this->m_buffer[i] = rhs(i);
    }
    return *this;
}

template <typename T, size_t N>
inline Tuple<T, N> operator-(const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret;
    for (int i = 0; i < N; i++)
    {
	ret(i) = -rhs(i);
    }
    return ret;
}

template <typename T, size_t N>
inline Tuple<T, N> operator+(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret;
    for (int i = 0; i < N; i++)
    {
	ret(i) = lhs(i) + rhs(i);
    }
    return ret;
}

template <typename T, size_t N>
inline Tuple<T, N> operator-(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret;
    for (int i = 0; i < N; i++)
    {
	ret(i) = lhs(i) - rhs(i);
    }
    return ret;
}

template <typename T, size_t N>
inline Tuple<T, N> operator*(const Tuple<T, N> &lhs, double s)
{
    Tuple<T, N> ret;
    for (int i = 0; i < N; i++)
    {
	ret(i) = lhs(i) * s;
    }
    return ret;
}

template <typename T, size_t N>
inline Tuple<T, N> operator/(const Tuple<T, N> &lhs, double s)
{
    return lhs * (1 / s);
}

template <typename T, size_t N>
inline Tuple<T, N>& operator+=(Tuple<T, N> &lhs, const Tuple<T, N> &rhs)
{
    for (int i = 0; i < N; i++)
    {
	lhs(i) += rhs(i);
    }
    return lhs;
}

template <typename T, size_t N>
inline std::ostream& operator<<(std::ostream &out, const Tuple<T, N> &rhs)
{
    for (int i = 0; i < N; i++)
    {
	out << rhs(i) << " ";
    }
    return out;
}

template <typename T>
inline Tuple<T, 4> reflect(const Tuple<T, 4> &in, const Tuple<T, 4> &normal)
{
    return in - normal * 2 * dot(in, normal);
}

template <typename T, size_t N>
inline double dot(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs)
{
    double total = 0;
    for (int i = 0; i < N; i++)
    {
	total += lhs(i) * rhs(i);
    }
    return total;
}

template <typename T>
inline Tuple<T, 4> cross(const Tuple<T, 4> &lhs, const Tuple<T, 4> &rhs)
{
    return vector(lhs(1) * rhs(2) - lhs(2) * rhs(1),
		  lhs(2) * rhs(0) - lhs(0) * rhs(2),
		  lhs(0) * rhs(1) - lhs(1) * rhs(0));
}

template <typename T, size_t N>
inline Tuple<T, N> hadamard_product(const Tuple<T, N> &lhs, const Tuple<T, N> &rhs)
{
    Tuple<T, N> ret;
    for (int i = 0; i < N; i++)
    {
	ret(i) = lhs(i) * rhs(i);
    }
    return ret;
}

template <typename T> 
inline Tuple<T, 4> point(T x, T y, T z)
{
    Tuple<T, 4> ret;
    ret(0) = x;
    ret(1) = y;
    ret(2) = z;
    ret(3) = 1;
    return ret;
}

template <typename T> 
inline Tuple<T, 4> vector(T x, T y, T z)
{
    Tuple<T, 4> ret;
    ret(0) = x;
    ret(1) = y;
    ret(2) = z;
    ret(3) = 0;
    return ret;
}

template <typename T> 
inline Tuple<T, 3> color(T r, T g, T b)
{
    Tuple<T, 3> ret;
    ret(0) = r;
    ret(1) = g;
    ret(2) = b;
    return ret;
}

// specializations
typedef Tuple<int, 1> Tuple1i;
typedef Tuple<float, 1> Tuple1f;
typedef Tuple<double, 1> Tuple1d;

typedef Tuple<int, 2> Tuple2i;
typedef Tuple<float, 2> Tuple2f;
typedef Tuple<double, 2> Tuple2d;

typedef Tuple<int, 3> Tuple3i;
typedef Tuple<float, 3> Tuple3f;
typedef Tuple<double, 3> Tuple3d;

typedef Tuple<int, 4> Tuple4i;
typedef Tuple<float, 4> Tuple4f;
typedef Tuple<double, 4> Tuple4d;

} // namespace math

#endif