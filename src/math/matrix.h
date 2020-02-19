#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "common.h"
#include "math/tuple.h"

class Matrix
{
private:
    // attributes
    int m_rows, m_columns;
    double **m_buffer;
    int *m_resources;

    // initialize and destroy methods
    void init();
    void destroy();

public:
    Matrix(int rows, int columns) :
	m_rows{rows},
	m_columns{columns}
    {
	init();
    }

    ~Matrix()
    {
	(*m_resources)--;
	if (*m_resources == 0)
	    destroy();
    }

    // copy overloads
    Matrix(const Matrix &m) :
	m_rows{m.m_rows},
	m_columns{m.m_columns},
	m_buffer{m.m_buffer},
	m_resources(m.m_resources)
    {
	(*m_resources)++;
    }

    Matrix& operator=(const Matrix &m)
    {
	if (&m == this)
	    return *this;

	(*m_resources)--;
	if (*m_resources == 0)
	    destroy();

	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_buffer = m.m_buffer;
	m_resources = m.m_resources;
	(*m_resources)++;

	return *this;
    }

    // accessor methods
    int rows() const {return m_rows;}
    int columns() const {return m_columns;}

    double get(int x, int y) const;
    void set(int x, int y, double value);

    // matrix operations
    Matrix transpose() const;
    Matrix submatrix(int row, int column) const;
    double cofactor(int row, int column) const;
    double determinant() const;
    Matrix inverse() const;

    // transformations
    Matrix translate(double x, double y, double z);

    Matrix scale(double x, double y, double z);

    Matrix rotate_x(double r);
    Matrix rotate_y(double r);
    Matrix rotate_z(double r);

    Matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

    // print overload
    friend std::ostream& operator<<(std::ostream &out, const Matrix &m);
};

// utility functions
bool compare(const Matrix &m1, const Matrix &m2);
Matrix multiply(const Matrix &m1, const Matrix &m2);
Tuple multiply(const Matrix &m, const Tuple &t);

// convenience functions
Matrix identity(int size = 4);

#endif