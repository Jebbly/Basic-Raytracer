#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "util/common.h"

class Tuple
{
private:
    double m_x, m_y, m_z, m_w;

public:
    Tuple(double x, double y, double z, double w) :
	m_x{x},
	m_y{y},
	m_z{z},
	m_w{w}
    {};

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

#ifdef DEBUG
    friend std::ostream& operator<<(std::ostream& out, const Tuple& tuple);
#endif
};

// convenience functions
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);

#endif