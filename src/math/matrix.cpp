#include "math/matrix.h"

Matrix::Matrix(int rows, int columns) :
    m_rows{rows},
    m_columns{columns}
{
    init();
}

Matrix::~Matrix()
{
    (*m_resources)--;
    if (*m_resources == 0)
	destroy();
}

// copy overloads
Matrix::Matrix(const Matrix &m) :
    m_rows{m.m_rows},
    m_columns{m.m_columns},
    m_buffer{m.m_buffer},
    m_resources(m.m_resources)
{
    (*m_resources)++;
}

Matrix& Matrix::operator=(const Matrix &m)
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

// initialize and destroy methods
void Matrix::init()
{
    m_buffer = new double*[m_rows];
    for (int i = 0; i < m_rows; i++)
    {
	m_buffer[i] = new double[m_columns];
    }

    m_resources = new int;
    *m_resources = 1;
}

void Matrix::destroy()
{
    for (int i = 0; i < m_rows; i++)
    {
	delete[] m_buffer[i];
    }
    delete[] m_buffer;

    delete m_resources;
}

// accessor methods
double Matrix::get(int y, int x) const
{
    assert(x >= 0 && x < get_columns() &&
	   y >= 0 && y < get_rows() &&
	   "index outside of matrix");

    return m_buffer[y][x];
}

void Matrix::set(int y, int x, double value)
{
    assert(x >= 0 && x < get_columns() &&
	   y >= 0 && y < get_rows() &&
	   "index outside of matrix");

    m_buffer[y][x] = value;
}

// matrix operations
Matrix Matrix::transpose() const
{
    Matrix ret{get_columns(), get_rows()};
    for (int i = 0; i < get_rows(); i++)
    {
	for (int j = 0; j < get_columns(); j++)
	{
	    ret.set(j, i, get(i, j));
	}
    }
    return ret;
}

Matrix Matrix::submatrix(int row, int column) const
{
    assert(row >= 0 && row < get_rows() &&
	   column >= 0 && column < get_columns() &&
	   "row or column outside of matrix");

    int x = 0, y = 0;
    Matrix ret{get_rows() - 1, get_columns() - 1};
    for (int i = 0; i < get_rows(); i++)
    {
	if (i == row) continue;
	for (int j = 0; j < get_columns(); j++)
	{
	    if (j == column) continue;
	    ret.set(x, y, get(i, j));
	    y++;
	}
	y = 0; x++;
    }
    return ret;
}

double Matrix::cofactor(int row, int column) const
{
    double minor = submatrix(row, column).determinant();
    return ((row + column) % 2 == 0) ? minor : -minor;
}

double Matrix::determinant() const
{
    assert(get_rows() == get_columns() &&
	   "non-square matrix given");

    if (get_rows() == 2)
	return get(0, 0) * get(1, 1) - get(1, 0) * get(0, 1);

    double total = 0;
    for (int i = 0; i < get_columns(); i++)
    {
	total += cofactor(0, i) * get(0, i);
    }
    return total;
}

Matrix Matrix::inverse() const
{
    double det = determinant();
    assert(det != 0 &&
	   "noninvertible matrix");

    Matrix ret{get_rows(), get_columns()};
    for (int i = 0; i < get_rows(); i++)
    {
	for (int j = 0; j < get_columns(); j++)
	{
	    ret.set(i, j, cofactor(i, j) / det);
	}
    }
    return ret.transpose();
}

// transformations
Matrix Matrix::translate(double x, double y, double z)
{
    Matrix ret = identity();

    ret.set(0, 3, x);
    ret.set(1, 3, y);
    ret.set(2, 3, z);

    return multiply(ret, *this);
}

Matrix Matrix::scale(double x, double y, double z)
{
    Matrix ret = identity();

    ret.set(0, 0, x);
    ret.set(1, 1, y);
    ret.set(2, 2, z);

    return multiply(ret, *this);
}

Matrix Matrix::rotate_x(double r)
{
    Matrix ret = identity();

    ret.set(1, 1, std::cos(r));
    ret.set(1, 2, -std::sin(r));
    ret.set(2, 1, std::sin(r));
    ret.set(2, 2, std::cos(r));

    return multiply(ret, *this);
}

Matrix Matrix::rotate_y(double r)
{
    Matrix ret = identity();

    ret.set(0, 0, std::cos(r));
    ret.set(0, 2, std::sin(r));
    ret.set(2, 0, -std::sin(r));
    ret.set(2, 2, std::cos(r));

    return multiply(ret, *this);
}

Matrix Matrix::rotate_z(double r)
{
    Matrix ret = identity();

    ret.set(0, 0, std::cos(r));
    ret.set(0, 1, -std::sin(r));
    ret.set(1, 0, std::sin(r));
    ret.set(1, 1, std::cos(r));

    return multiply(ret, *this);
}

Matrix Matrix::shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
    Matrix ret = identity();

    ret.set(0, 1, x_y);
    ret.set(0, 2, x_z);
    ret.set(1, 0, y_x);
    ret.set(1, 2, y_z);
    ret.set(2, 0, z_x);
    ret.set(2, 1, z_y);

    return multiply(ret, *this);
}

// utility functions
bool compare(const Matrix &m1, const Matrix &m2)
{
    if (m1.get_rows() != m2.get_rows() ||
	m1.get_columns() != m2.get_columns())
	return false;

    for (int i = 0; i < m1.get_rows(); i++)
    {
	for (int j = 0; j < m1.get_columns(); j++)
	{
	    if (m1.get(i, j) != m2.get(i, j))
		return false;
	}
    }
    return true;
}

Matrix multiply(const Matrix &m1, const Matrix &m2)
{
    assert(m1.get_columns() == m2.get_rows() &&
	   "cannot multiply matrices");

    Matrix ret{m1.get_rows(), m2.get_columns()};
    for (int i = 0; i < m1.get_rows(); i++)
    {
	for (int j = 0; j < m2.get_columns(); j++)
	{
	    double total = 0;
	    for (int k = 0; k < m1.get_columns(); k++)
	    {
		total += m1.get(i, k) * m2.get(k, j);
	    }
	    ret.set(i, j, total);
	}
    }
    return ret;
}

Tuple multiply(const Matrix &m, const Tuple &t)
{
    assert(m.get_rows() == t.get_size() &&
	   "incompatible matrix and tuple multiplication");

    Tuple ret{t.get_size()};
    for (int i = 0; i < m.get_rows(); i++)
    {
	double total = 0;
	for (int j = 0; j < m.get_columns(); j++)
	{
	    total += m.get(i, j) * t.get(j);
	}
	ret.set(i, total);
    }
    return ret;
}

// convenience functions
Matrix identity(int size)
{
    Matrix ret{size, size};
    for (int i = 0; i < size; i++)
    {
	for (int j = 0; j < size; j++)
	{
	    if (i == j)
		ret.set(i, j, 1.0);
	    else
		ret.set(i, j, 0.0);
	}
    }
    return ret;
}

Matrix view(const Tuple &from, const Tuple &to, const Tuple &up)
{
    Tuple forward = normalize(to - from);
    Tuple left = cross(forward, normalize(up));
    Tuple true_up = cross(left, forward);

    Matrix orientation{identity()};

    for (int i = 0; i < 3; i++)
    {
	orientation.set(0, i, left.get(i));
    }

    for (int i = 0; i < 3; i++)
    {
	orientation.set(1, i, true_up.get(i));
    }

    for (int i = 0; i < 3; i++)
    {
	orientation.set(2, i, -forward.get(i));
    }

    return multiply(orientation, identity().translate(-from.get(0), -from.get(1), -from.get(2)));
}

// print overload
std::ostream& operator<<(std::ostream& out, const Matrix &m)
{
    for (int i = 0; i < m.get_rows(); i++)
    {
	for (int j = 0; j < m.get_columns(); j++)
	{
	    out << m.get(i, j) << ' '; 
	}
	out << '\n';
    }
    return out;
}