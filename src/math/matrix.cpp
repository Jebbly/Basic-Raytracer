#include "math/matrix.h"

math::Matrix4d::Matrix4d()
{
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    m_buffer[i][j] = 0;
	}
    }
}

// copy overloads
math::Matrix4d::Matrix4d(const math::Matrix4d &rhs)
{
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    m_buffer[i][j] = rhs(i, j);
	}
    }
}

math::Matrix4d& math::Matrix4d::operator=(const math::Matrix4d &rhs)
{
    if (this == &rhs)
	return *this;

    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    m_buffer[i][j] = rhs.m_buffer[i][j];
	}
    }

    return *this;
}

// accessor methods
double& math::Matrix4d::operator()(const size_t row, const size_t col)
{
    assert(row < 4 && col < 4 && "index out of bounds");
    return m_buffer[row][col];
}

const double& math::Matrix4d::operator()(const size_t row, const size_t col) const
{
    assert(row < 4 && col < 4 && "index out of bounds");
    return m_buffer[row][col];
}

// transformations
math::Matrix4d math::Matrix4d::translate(double x, double y, double z) const
{
    Matrix4d ret{identity()};
    ret(0, 3) = x;
    ret(1, 3) = y;
    ret(2, 3) = z;
    return (ret * (*this));
}

math::Matrix4d math::Matrix4d::scale(double x, double y, double z) const
{
    Matrix4d ret{identity()};
    ret(0, 0) = x;
    ret(1, 1) = y;
    ret(2, 2) = z;
    return (ret * (*this));
}

math::Matrix4d math::Matrix4d::rotate_x(double r) const
{
    Matrix4d ret{identity()};
    ret(1, 1) = std::cos(r);
    ret(1, 2) = -std::sin(r);
    ret(2, 1) = std::sin(r);
    ret(2, 2) = std::cos(r);
    return (ret * (*this));
}

math::Matrix4d math::Matrix4d::rotate_y(double r) const
{
    Matrix4d ret{identity()};
    ret(0, 0) = std::cos(r);
    ret(0, 2) = std::sin(r);
    ret(2, 0) = -std::sin(r);
    ret(2, 2) = std::cos(r);
    return (ret * (*this));
}

math::Matrix4d math::Matrix4d::rotate_z(double r) const
{
    Matrix4d ret{identity()};
    ret(0, 0) = std::cos(r);
    ret(0, 1) = -std::sin(r);
    ret(1, 0) = std::sin(r);
    ret(1, 1) = std::cos(r);
    return (ret * (*this));
}

math::Matrix4d math::Matrix4d::shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) const
{
    Matrix4d ret{identity()};
    ret(0, 1) = x_y;
    ret(0, 2) = x_z;
    ret(1, 0) = y_x;
    ret(1, 2) = y_z;
    ret(2, 0) = z_x;
    ret(2, 1) = z_y;
    return (ret * (*this));
}

// utility functions
math::Matrix4d math::Matrix4d::inverse() const
{
    Matrix4d ret{};
    
    ret(0, 0) = m_buffer[1][1] * m_buffer[2][2] * m_buffer[3][3] -
		m_buffer[1][1]  * m_buffer[2][3] * m_buffer[3][2] - 
		m_buffer[2][1]  * m_buffer[1][2]  * m_buffer[3][3] + 
		m_buffer[2][1]  * m_buffer[1][3]  * m_buffer[3][2] +
		m_buffer[3][1] * m_buffer[1][2]  * m_buffer[2][3] - 
		m_buffer[3][1] * m_buffer[1][3]  * m_buffer[2][2];

    ret(1, 0) = -m_buffer[1][0]  * m_buffer[2][2] * m_buffer[3][3] + 
		m_buffer[1][0]  * m_buffer[2][3] * m_buffer[3][2] + 
		m_buffer[2][0]  * m_buffer[1][2]  * m_buffer[3][3] - 
		m_buffer[2][0]  * m_buffer[1][3]  * m_buffer[3][2] - 
		m_buffer[3][0] * m_buffer[1][2]  * m_buffer[2][3] + 
		m_buffer[3][0] * m_buffer[1][3]  * m_buffer[2][2];

    ret(2, 0) = m_buffer[1][0]  * m_buffer[2][1] * m_buffer[3][3] - 
		m_buffer[1][0]  * m_buffer[2][3] * m_buffer[3][1] - 
		m_buffer[2][0]  * m_buffer[1][1] * m_buffer[3][3] + 
		m_buffer[2][0]  * m_buffer[1][3] * m_buffer[3][1] + 
		m_buffer[3][0] * m_buffer[1][1] * m_buffer[2][3] - 
		m_buffer[3][0] * m_buffer[1][3] * m_buffer[2][1];

    ret(3, 0) = -m_buffer[1][0]  * m_buffer[2][1] * m_buffer[3][2] + 
		m_buffer[1][0]  * m_buffer[2][2] * m_buffer[3][1] +
		m_buffer[2][0]  * m_buffer[1][1] * m_buffer[3][2] - 
		m_buffer[2][0]  * m_buffer[1][2] * m_buffer[3][1] - 
		m_buffer[3][0] * m_buffer[1][1] * m_buffer[2][2] + 
		m_buffer[3][0] * m_buffer[1][2] * m_buffer[2][1];

    ret(0, 1) = -m_buffer[0][1] * m_buffer[2][2] * m_buffer[3][3] +
		m_buffer[0][1]  * m_buffer[2][3] * m_buffer[3][2] + 
		m_buffer[2][1]  * m_buffer[0][2] * m_buffer[3][3] - 
		m_buffer[2][1]  * m_buffer[0][3] * m_buffer[3][2] - 
		m_buffer[3][1] * m_buffer[0][2] * m_buffer[2][3] + 
		m_buffer[3][1] * m_buffer[0][3] * m_buffer[2][2];

    ret(1, 1) = m_buffer[0][0]  * m_buffer[2][2] * m_buffer[3][3] - 
		m_buffer[0][0]  * m_buffer[2][3] * m_buffer[3][2] - 
		m_buffer[2][0]  * m_buffer[0][2] * m_buffer[3][3] + 
		m_buffer[2][0]  * m_buffer[0][3] * m_buffer[3][2] + 
		m_buffer[3][0] * m_buffer[0][2] * m_buffer[2][3] - 
		m_buffer[3][0] * m_buffer[0][3] * m_buffer[2][2];

    ret(2, 1) = -m_buffer[0][0]  * m_buffer[2][1] * m_buffer[3][3] + 
		m_buffer[0][0]  * m_buffer[2][3] * m_buffer[3][1] + 
		m_buffer[2][0]  * m_buffer[0][1] * m_buffer[3][3] - 
		m_buffer[2][0]  * m_buffer[0][3] * m_buffer[3][1] - 
		m_buffer[3][0] * m_buffer[0][1] * m_buffer[2][3] + 
		m_buffer[3][0] * m_buffer[0][3] * m_buffer[2][1];

    ret(3, 1) = m_buffer[0][0]  * m_buffer[2][1] * m_buffer[3][2] - 
		m_buffer[0][0]  * m_buffer[2][2] * m_buffer[3][1] - 
		m_buffer[2][0]  * m_buffer[0][1] * m_buffer[3][2] + 
		m_buffer[2][0]  * m_buffer[0][2] * m_buffer[3][1] + 
		m_buffer[3][0] * m_buffer[0][1] * m_buffer[2][2] - 
		m_buffer[3][0] * m_buffer[0][2] * m_buffer[2][1];

    ret(0, 2) = m_buffer[0][1]  * m_buffer[1][2] * m_buffer[3][3] - 
		m_buffer[0][1]  * m_buffer[1][3] * m_buffer[3][2] - 
		m_buffer[1][1]  * m_buffer[0][2] * m_buffer[3][3] + 
		m_buffer[1][1]  * m_buffer[0][3] * m_buffer[3][2] + 
		m_buffer[3][1] * m_buffer[0][2] * m_buffer[1][3] - 
		m_buffer[3][1] * m_buffer[0][3] * m_buffer[1][2];

    ret(1, 2) = -m_buffer[0][0]  * m_buffer[1][2] * m_buffer[3][3] + 
		m_buffer[0][0]  * m_buffer[1][3] * m_buffer[3][2] + 
		m_buffer[1][0]  * m_buffer[0][2] * m_buffer[3][3] - 
		m_buffer[1][0]  * m_buffer[0][3] * m_buffer[3][2] - 
		m_buffer[3][0] * m_buffer[0][2] * m_buffer[1][3] + 
		m_buffer[3][0] * m_buffer[0][3] * m_buffer[1][2];

    ret(2, 2) = m_buffer[0][0]  * m_buffer[1][1] * m_buffer[3][3] - 
		m_buffer[0][0]  * m_buffer[1][3] * m_buffer[3][1] - 
		m_buffer[1][0]  * m_buffer[0][1] * m_buffer[3][3] + 
		m_buffer[1][0]  * m_buffer[0][3] * m_buffer[3][1] + 
		m_buffer[3][0] * m_buffer[0][1] * m_buffer[1][3] - 
		m_buffer[3][0] * m_buffer[0][3] * m_buffer[1][1];

    ret(3, 2) = -m_buffer[0][0]  * m_buffer[1][1] * m_buffer[3][2] + 
		m_buffer[0][0]  * m_buffer[1][2] * m_buffer[3][1] + 
		m_buffer[1][0]  * m_buffer[0][1] * m_buffer[3][2] - 
		m_buffer[1][0]  * m_buffer[0][2] * m_buffer[3][1] - 
		m_buffer[3][0] * m_buffer[0][1] * m_buffer[1][2] + 
		m_buffer[3][0] * m_buffer[0][2] * m_buffer[1][1];

    ret(0, 3) = -m_buffer[0][1] * m_buffer[1][2] * m_buffer[2][3] + 
		m_buffer[0][1] * m_buffer[1][3] * m_buffer[2][2] + 
		m_buffer[1][1] * m_buffer[0][2] * m_buffer[2][3] - 
		m_buffer[1][1] * m_buffer[0][3] * m_buffer[2][2] - 
		m_buffer[2][1] * m_buffer[0][2] * m_buffer[1][3] + 
		m_buffer[2][1] * m_buffer[0][3] * m_buffer[1][2];

    ret(1, 3) = m_buffer[0][0] * m_buffer[1][2] * m_buffer[2][3] - 
		m_buffer[0][0] * m_buffer[1][3] * m_buffer[2][2] - 
		m_buffer[1][0] * m_buffer[0][2] * m_buffer[2][3] + 
		m_buffer[1][0] * m_buffer[0][3] * m_buffer[2][2] + 
		m_buffer[2][0] * m_buffer[0][2] * m_buffer[1][3] - 
		m_buffer[2][0] * m_buffer[0][3] * m_buffer[1][2];

    ret(2, 3) = -m_buffer[0][0] * m_buffer[1][1] * m_buffer[2][3] + 
		m_buffer[0][0] * m_buffer[1][3] * m_buffer[2][1] + 
		m_buffer[1][0] * m_buffer[0][1] * m_buffer[2][3] - 
		m_buffer[1][0] * m_buffer[0][3] * m_buffer[2][1] - 
		m_buffer[2][0] * m_buffer[0][1] * m_buffer[1][3] + 
		m_buffer[2][0] * m_buffer[0][3] * m_buffer[1][1];

    ret(3, 3) = m_buffer[0][0] * m_buffer[1][1] * m_buffer[2][2] - 
		m_buffer[0][0] * m_buffer[1][2] * m_buffer[2][1] - 
		m_buffer[1][0] * m_buffer[0][1] * m_buffer[2][2] + 
		m_buffer[1][0] * m_buffer[0][2] * m_buffer[2][1] + 
		m_buffer[2][0] * m_buffer[0][1] * m_buffer[1][2] - 
		m_buffer[2][0] * m_buffer[0][2] * m_buffer[1][1];

    double det = m_buffer[0][0] * ret(0, 0) + m_buffer[0][1] * ret(1, 0) + m_buffer[0][2] * ret(2, 0) + m_buffer[0][3] * ret(3, 0);
    assert(det != 0 && "non-invertible matrix");
    return ret / det;
}

math::Matrix4d math::Matrix4d::transpose() const
{
    Matrix4d ret{};
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    ret(j, i) = m_buffer[i][j];
	}
    }
    return ret;
}

// arithmetic overloads
math::Matrix4d math::operator*(const math::Matrix4d &lhs, double rhs)
{
    Matrix4d ret{};
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    ret(i, j) = lhs(i, j) * rhs;
	}
    }
    return ret;
}

math::Matrix4d math::operator/(const math::Matrix4d &lhs, double rhs)
{
    return lhs * (1 / rhs);
}

math::Matrix4d math::operator*(const math::Matrix4d &lhs, const math::Matrix4d &rhs)
{
    math::Matrix4d ret{};
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    double sum = 0;
	    for (int k = 0; k < 4; k++)
	    {
		sum += lhs(i, k) * rhs(k, j);
	    }
	    ret(i, j) = sum;
	}
    }
    return ret;
}

math::Tuple4d math::operator*(const math::Matrix4d &lhs, const math::Tuple4d &rhs)
{
    math::Tuple4d ret{};
    for (int i = 0; i < 4; i++)
    {
	double sum = 0;
	for (int j = 0; j < 4; j++)
	{
	    sum += lhs(i, j) * rhs(j);
	}
	ret(i) = sum;
    }
    return ret;
}

// convenience functions
math::Matrix4d math::identity()
{
    math::Matrix4d ret{};
    for (int i = 0; i < 4; i++)
    {
	for (int j = 0; j < 4; j++)
	{
	    if (i == j)
		ret(i, j) = 1;
	}
    }
    return ret;
}

math::Matrix4d math::view(const math::Tuple4d &from, const math::Tuple4d &to, const math::Tuple4d &up)
{
    math::Tuple4d forward = (to - from).normalize();
    math::Tuple4d left = cross(forward, up.normalize());
    math::Tuple4d true_up = cross(left, forward);

    math::Matrix4d ret{identity()};

    for (int i = 0; i < 3; i++)
    {
	ret(0, i) = left(i);
    }

    for (int i = 0; i < 3; i++)
    {
	ret(1, i) = true_up(i);
    }

    for (int i = 0; i < 3; i++)
    {
	ret(2, i) = -forward(i);
    }

    return (ret * identity().translate(-from(0), -from(1), -from(2)));
}