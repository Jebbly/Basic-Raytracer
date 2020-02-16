#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "util/common.h"

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
	    m_buffer[i] = new double[m_columns];
    }

    ~Matrix()
    {
	if (m_buffer)
	{
	    for (int i = 0; i < m_rows; i++)
		delete[] m_buffer[i];
	    delete[] m_buffer;
	}
    }

    // move semantics
    Matrix(Matrix&& m) :
	m_rows{m.m_rows},
	m_columns{m.m_columns},
	m_buffer{m.m_buffer}
    {
	m.m_buffer = nullptr;
    }

    Matrix& operator=(Matrix &&m);

    // accessor methods
    double get(int x, int y) const;
    void set(int x, int y, double value);

    // matrix operations
    friend bool compare(const Matrix &m1, const Matrix &m2);
    friend Matrix multiply(const Matrix &m1, const Matrix &m2);
    Matrix transpose() const;
    Matrix submatrix(int row, int column) const;
    double cofactor(int row, int column) const;
    double determinant() const;
    Matrix inverse() const;

    // print overload
    friend std::ostream& operator<<(std::ostream& out, const Matrix &m);
};

// convenience functions
Matrix identity(int size = 4);

#endif