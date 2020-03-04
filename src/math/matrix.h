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
    Matrix(int rows, int columns);
    ~Matrix();

    // copy overloads
    Matrix(const Matrix &m);
    Matrix& operator=(const Matrix &m);

    // accessor methods
    int get_rows() const {return m_rows;}
    int get_columns() const {return m_columns;}

    double get(int y, int x) const;
    void set(int y, int x, double value);

    // matrix operations
    Matrix transpose() const;
    Matrix submatrix(int row, int column) const;
    double cofactor(int row, int column) const;
    double determinant() const;
    Matrix inverse() const;

    // transformations
    Matrix translate(double x, double y, double z) const;

    Matrix scale(double x, double y, double z) const;

    Matrix rotate_x(double r) const;
    Matrix rotate_y(double r) const;
    Matrix rotate_z(double r) const;

    Matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) const;

    // print overload
    friend std::ostream& operator<<(std::ostream &out, const Matrix &m);
};

// utility functions
bool compare(const Matrix &m1, const Matrix &m2);
Matrix multiply(const Matrix &m1, const Matrix &m2);
Tuple multiply(const Matrix &m, const Tuple &t);

// convenience functions
Matrix identity(int size = 4);
Matrix view(const Tuple &from, const Tuple &to, const Tuple &up);

#endif