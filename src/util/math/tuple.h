#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "util/common.h"

class Tuple
{
private:
    int m_size;
    double *m_buffer;

public:
    Tuple() :
	m_size{3}
    {
	m_buffer = new double[m_size];
    }

    Tuple(int size) :
	m_size{size}
    {
	m_buffer = new double[m_size];
    };

    ~Tuple()
    {
	if (m_buffer != nullptr)
	    delete[] m_buffer;
    }

    Tuple& operator=(const Tuple &t)
    {
	if (&t == this)
	    return *this;

	delete m_buffer;

	m_size = t.m_size;
	m_buffer = new double[m_size];
	for (int i = 0; i < m_size; i++)
	    m_buffer[i] = t.m_buffer[i];

	return *this;
    }

    // move semantics
    Tuple(Tuple &&t) :
	m_size{t.m_size},
	m_buffer{t.m_buffer}
    {
	t.m_buffer = nullptr;
    }

    Tuple& operator=(Tuple &&t)
    {
	if (&t == this)
	    return *this;

	delete[] m_buffer;

	m_size = t.m_size;
	m_buffer = t.m_buffer;
	t.m_buffer = nullptr;

	return *this;
    }

    // accessor methods
    double get(int index) const;
    void set(int index, double value);

    // arithmetic overloads
    Tuple operator-() const;
    friend Tuple operator+(const Tuple &t1, const Tuple &t2);
    friend Tuple operator-(const Tuple &t1, const Tuple &t2);
    friend Tuple operator*(const Tuple &t, float s);
    friend Tuple operator/(const Tuple &t, float s);
    
    // utility functions
    friend double magnitude(const Tuple &t);
    friend Tuple normalize(const Tuple &t);
    friend double dot(const Tuple &t1, const Tuple &t2);
    friend Tuple cross(const Tuple &t1, const Tuple &t2);
    friend Tuple hadamard_product(const Tuple &t1, const Tuple &t2);

    // print overload
    friend std::ostream& operator<<(std::ostream& out, const Tuple& t);
};

// convenience functions
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
Tuple color(double r, double g, double b);

#endif