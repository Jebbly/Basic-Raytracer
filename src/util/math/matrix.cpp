#include "util/math/matrix.h"

// accessor methods
double Matrix::get(int x, int y) const
{
    assert(x >= 0 && x < m_columns &&
	   y >= 0 && y < m_rows &&
	   "index outside of matrix");

    return m_buffer[y][x];
}

void Matrix::set(int x, int y, double value)
{
    assert(x >= 0 && x < m_columns &&
	   y >= 0 && y < m_rows &&
	   "index outside of matrix");

    m_buffer[y][x] = value;
}

// matrix operations
bool compare(const Matrix &m1, const Matrix &m2)
{
    if (m1.m_rows != m2.m_rows ||
	m1.m_columns != m2.m_columns)
	return false;

    for (int i = 0; i < m1.m_rows; i++)
    {
	for (int j = 0; j < m1.m_columns; j++)
	{
	    if (m1.get(i, j) != m2.get(i, j))
		return false;
	}
    }
    return true;
}

Matrix multiply(const Matrix &m1, const Matrix &m2)
{
    assert(m1.m_columns == m2.m_rows &&
	   "cannot multiply matrices");
    
    Matrix ret = Matrix{ m1.m_rows, m2.m_columns};
    for (int i = 0; i < m1.m_rows; i++)
    {
	for (int j = 0; j < m2.m_columns; j++)
	{
	    double total = 0;
	    for (int k = 0; k < m1.m_columns; k++)
	    {
		total += m1.get(i, k) * m2.get(k, j);
	    }
	    ret.set(i, j, total);
	}
    }
    return ret;
}

Matrix Matrix::transpose() const
{
    Matrix ret{m_columns, m_rows};
    for (int i = 0; i < m_rows; i++)
    {
	for (int j = 0; j < m_columns; j++)
	{
	    ret.set(j, i, get(i, j));
	}
    }
    return ret;
}

Matrix Matrix::submatrix(int row, int column) const
{
    assert(row >= 0 && row < m_rows &&
	   column >= 0 && column < m_columns &&
	   "row or column outside of matrix");

    int x = 0, y = 0;
    Matrix ret{ m_rows - 1, m_columns - 1 };
    for (int i = 0; i < m_rows; i++)
    {
	if (i == row) continue;
	for (int j = 0; j < m_columns; j++)
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
    assert(m_rows == m_columns &&
	   "non-square matrix given");

    if (m_rows == 2)
	return get(0, 0) * get(1, 1) - get(1, 0) * get(0, 1);

    double total = 0;
    for (int i = 0; i < m_columns; i++)
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

    Matrix ret{m_rows, m_columns};
    for (int i = 0; i < m_rows; i++)
    {
	for (int j = 0; j < m_columns; j++)
	{
	    ret.set(i, j, cofactor(i, j) / det);
	}
    }
    return ret.transpose();
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

// print overload
std::ostream& operator<<(std::ostream& out, const Matrix &m)
{
    for (int i = 0; i < m.m_rows; i++)
    {
	for (int j = 0; j < m.m_columns; j++)
	{
	    out << m.get(i, j) << ' '; 
	}
	out << '\n';
    }
    return out;
}