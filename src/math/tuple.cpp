#include "math/tuple.h"

Tuple::Tuple(int size) :
    m_size{size}
{
    init();
};

Tuple::~Tuple()
{
    (*m_resources)--;
    if (*m_resources == 0)
	destroy();
}

// copy overloads
Tuple::Tuple(const Tuple &t) :
    m_size{t.m_size},
    m_buffer{t.m_buffer},
    m_resources{t.m_resources}
{
    (*m_resources)++;
}

Tuple& Tuple::operator=(const Tuple &t)
{
    if (&t == this)
	return *this;

    (*m_resources)--;
    if (*m_resources == 0)
	destroy();

    m_size = t.m_size;
    m_buffer = t.m_buffer;
    m_resources = t.m_resources;
    (*m_resources)++;

    return *this;
}

// initialize and destroy methods
void Tuple::init()
{
    m_buffer = new double[m_size];

    m_resources = new int;
    *m_resources = 1;
}

void Tuple::destroy()
{
    delete[] m_buffer;

    delete m_resources;
}

// accessor methods
double Tuple::get(int index) const
{
    assert(index >= 0 && index < get_size() &&
	   "index out of bounds");

    return m_buffer[index];
}

void Tuple::set(int index, double value)
{
    assert(index >= 0 && index < get_size() &&
	   "index out of bounds");

    m_buffer[index] = value;
}

// arithmetic overloads
Tuple Tuple::operator-() const
{
    Tuple ret{get_size()};
    for (int i = 0; i < get_size(); i++)
    {
	ret.set(i, -get(i));
    }
    return ret;
}

Tuple operator+(const Tuple &t1, const Tuple &t2)
{
    assert(t1.get_size() == t2.get_size() &&
	   "cannot add differently sized tuples");

    Tuple ret{t1.get_size()};
    for (int i = 0; i < t1.get_size(); i++)
    {
	ret.set(i, t1.get(i) + t2.get(i));
    }
    return ret;
}

Tuple operator-(const Tuple &t1, const Tuple &t2)
{
    assert(t1.get_size() == t2.get_size() &&
	   "cannot subtract differently sized tuples");

    Tuple ret{t1.get_size()};
    for (int i = 0; i < t1.get_size(); i++)
    {
	ret.set(i, t1.get(i) - t2.get(i));
    }
    return ret;
}

Tuple operator*(const Tuple &t, double s)
{
    Tuple ret{t.get_size()};
    for (int i = 0; i < t.get_size(); i++)
    {
	ret.set(i, t.get(i) * s);
    }
    return ret;
}

Tuple operator/(const Tuple &t, double s)
{
    Tuple ret{t.get_size()};
    for (int i = 0; i < t.get_size(); i++)
    {
	ret.set(i, t.get(i) / s);
    }
    return ret;
}

Tuple& Tuple::operator+=(const Tuple &t)
{
    assert(get_size() == t.get_size() &&
	   "cannot add differently sized tuples");

    for (int i = 0; i < get_size(); i++)
    {
	m_buffer[i] += t.get(i);
    }
    return *this;
}

// utility functions
double magnitude(const Tuple &t)
{
    double total = 0;
    for (int i = 0; i < t.get_size(); i++)
    {
	total += pow(t.get(i), 2);
    }
    return sqrt(total);
}

Tuple normalize(const Tuple &t)
{
    return t / magnitude(t);
}

Tuple reflect(const Tuple &in, const Tuple &normal)
{
    return in - normal * 2 * dot(in, normal);
}

double dot(const Tuple &t1, const Tuple &t2)
{
    assert(t1.get_size() == t2.get_size() &&
	   "cannot dot differently sized tuples");

    double total = 0;
    for (int i = 0; i < t1.get_size(); i++)
    {
	total += t1.get(i) * t2.get(i);
    }
    return total;
}

Tuple cross(const Tuple &t1, const Tuple &t2)
{
    assert(t1.get_size() == 4 && t2.get_size() == 4 &&
	   "cannot cross non-vectors");

    return vector(t1.get(1) * t2.get(2) - t1.get(2) * t2.get(1),
		  t1.get(2) * t2.get(0) - t1.get(0) * t2.get(2),
		  t1.get(0) * t2.get(1) - t1.get(1) * t2.get(0));
}

Tuple hadamard_product(const Tuple &t1, const Tuple &t2)
{
    assert(t1.get_size() == 3 &&
	   "cannot take hadamard product of non-color");

    return color(t1.get(0) * t2.get(0),
		 t1.get(1) * t2.get(1),
		 t1.get(2) * t2.get(2));
}

// print overload
std::ostream& operator<<(std::ostream& out, const Tuple& t)
{
    for (int i = 0; i < t.get_size(); i++)
    {
	out << t.get(i) << ' ';
    }
    return out;
}

// convenience functions
Tuple point(double x, double y, double z)
{
    Tuple ret{4};
    ret.set(0, x);
    ret.set(1, y);
    ret.set(2, z);
    ret.set(3, 1.0);
    return ret;
}

Tuple vector(double x, double y, double z)
{
    Tuple ret{4};
    ret.set(0, x);
    ret.set(1, y);
    ret.set(2, z);
    ret.set(3, 0.0);
    return ret;
}

Tuple color(double r, double g, double b)
{
    Tuple ret{3};
    ret.set(0, r);
    ret.set(1, g);
    ret.set(2, b);
    return ret;
}
