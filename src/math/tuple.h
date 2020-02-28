#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include <cmath>
#include "common.h"

class Tuple
{
private:
    // attributes
    int m_size;
    double *m_buffer;
    int *m_resources;

    // initialize and destroy methods
    void init();
    void destroy();

public:
    Tuple(int size = 3);
    ~Tuple();

    // copy overloads
    Tuple(const Tuple &t);
    Tuple& operator=(const Tuple &t);

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
    friend std::ostream& operator<<(std::ostream &out, const Tuple &t);
};

// utility functions
double magnitude(const Tuple &t);
Tuple normalize(const Tuple &t);
Tuple reflect(const Tuple &in, const Tuple &normal);
double dot(const Tuple &t1, const Tuple &t2);
Tuple cross(const Tuple &t1, const Tuple &t2);
Tuple hadamard_product(const Tuple &t1, const Tuple &t2);

// convenience functions
Tuple point(double x, double y, double z);
Tuple vector(double x, double y, double z);
Tuple color(double r, double g, double b);

#endif