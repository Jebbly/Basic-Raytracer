#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "common.h"
#include "math/tuple.h"

class Matrix
{
private:
    int m_rows, m_columns;
    double **m_buffer;

public:
    Matrix(int rows, int columns) :
	m_rows{rows},
	m_columns{columns}
    {
	m_buffer = new double*[m_rows];
	for (int i = 0; i < m_rows; i++)
	{
	    m_buffer[i] = new double[m_columns];
	}
    }

    ~Matrix()
    {
	if (m_buffer)
	{
	    for (int i = 0; i < m_rows; i++)
	    {
		delete[] m_buffer[i];
	    }
	    delete[] m_buffer;
	}
    }

    // move semantics
    Matrix(Matrix &&m) :
	m_rows{m.m_rows},
	m_columns{m.m_columns},
	m_buffer{m.m_buffer}
    {
	m.m_buffer = nullptr;
    }

    Matrix& operator=(Matrix &&m)
    {
	if (&m == this)
	    return *this;

	for (int i = 0; i < m_rows; i++)
	{
	    delete[] m_buffer[i];
	}
	delete[] m_buffer;

	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_buffer = m.m_buffer;
	m.m_buffer = nullptr;

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
    friend std::ostream& operator<<(std::ostream& out, const Matrix &m);
};

// utility functions
bool compare(const Matrix &m1, const Matrix &m2);
Matrix multiply(const Matrix &m1, const Matrix &m2);
Tuple multiply(const Matrix &m, const Tuple &t);

// convenience functions
Matrix identity(int size = 4);

#endif