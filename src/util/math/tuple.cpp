#include "tuple.h"

// arithmetic overloads
Tuple Tuple::operator-() const
{
    return Tuple(-m_x, -m_y, -m_z, -m_w);
}

Tuple operator+(const Tuple &t1, const Tuple &t2)
{
    return Tuple(t1.m_x + t2.m_x, 
		 t1.m_y + t2.m_y, 
		 t1.m_z + t2.m_z, 
		 t1.m_w + t2.m_w);
}

Tuple operator-(const Tuple &t1, const Tuple &t2)
{
    return Tuple(t1.m_x - t2.m_x, 
		 t1.m_y - t2.m_y, 
		 t1.m_z - t2.m_z, 
		 t1.m_w - t2.m_w);
}

Tuple operator*(const Tuple &t, float s)
{
    return Tuple(s * t.m_x, 
		 s * t.m_y, 
		 s * t.m_z, 
		 s * t.m_w);
}

Tuple operator/(const Tuple &t, float s)
{
    return Tuple(t.m_x / s, 
		 t.m_y / s, 
		 t.m_z / s, 
		 t.m_w / s);
}

// utility functions
double magnitude(const Tuple &t)
{
    return sqrt(pow(t.m_x, 2) + 
		pow(t.m_y, 2) + 
		pow(t.m_z, 2) + 
		pow(t.m_w, 2));
}

Tuple normalize(const Tuple &t)
{
    return t / magnitude(t);
}

double dot(const Tuple &t1, const Tuple &t2)
{
    return t1.m_x * t2.m_x + 
	   t1.m_y * t2.m_y + 
	   t1.m_z * t2.m_z + 
	   t1.m_w * t2.m_w;
}

Tuple cross(const Tuple &t1, const Tuple &t2)
{
    return vector(t1.m_y * t2.m_z - t1.m_z * t2.m_y,
		  t1.m_z * t2.m_x - t1.m_x * t2.m_z,
		  t1.m_x * t2.m_y - t1.m_y * t2.m_x);
}

// convenience functions
Tuple point(double x, double y, double z)
{
    return Tuple(x, y, z, 1.0);
}

Tuple vector(double x, double y, double z)
{
    return Tuple(x, y, z, 0.0);
}

#ifdef DEBUG
std::ostream& operator<<(std::ostream& out, const Tuple& tuple)
{
    out << "Tuple(" << tuple.m_x << ", " << tuple.m_y << ", " << tuple.m_z << ", " << tuple.m_w << ")";
    return out;
}
#endif