#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "common.h"

class Tuple
{
private:
    int m_size;
    double *m_buffer;
    int *m_resources;

public:
    Tuple() :
	m_size{3}
    {
	m_buffer = new double[m_size];

	m_resources = new int;
	*m_resources = 1;
    }

    Tuple(int size) :
	m_size{size}
    {
	m_buffer = new double[m_size];

	m_resources = new int;
	*m_resources = 1;
    };

    ~Tuple()
    {
	(*m_resources)--;
	if (*m_resources == 0)
	{
	    delete[] m_buffer;
	    delete m_resources;
	}
    }

    // move semantics
    Tuple(Tuple &&t) :
	m_size{t.m_size},
	m_buffer{t.m_buffer},
	m_resources{t.m_resources}
    {
	(*m_resources)++;
    }

    Tuple& operator=(Tuple &&t)
    {
	if (&t == this)
	    return *this;

	if (*m_resources == 1)
	{
	    delete[] m_buffer;
	    delete m_resources;
	}

	m_size = t.m_size;
	m_buffer = t.m_buffer;
	m_resources = t.m_resources;
	(*m_resources)++;

	return *this;
    }

    // accessor methods
    int size() const {return m_size;}

    double get(int index) const;
    void set(int index, double value);

    // arithmetic overloads
    Tuple operator-() const;
    friend Tuple operator+(const Tuple &t1, const Tuple &t2);
    friend Tuple operator-(const Tuple &t1, const Tuple &t2);
    friend Tuple operator*(const Tuple &t, float s);
    friend Tuple operator/(const Tuple &t, float s);

    // print overload
    friend std::ostream& operator<<(std::ostream& out, const Tuple& t);
};

// utility functions
double magnitude(const Tuple &t);
Tuple normalize(const Tuple &t);
double dot(const Tuple &t1, const Tuple &t2);
Tuple cross(const Tuple &t1, const Tuple &t2);
Tuple hadamard_product(const Tuple &t1, const Tuple &t2);

// convenience functions
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
Tuple color(double r, double g, double b);

#endif