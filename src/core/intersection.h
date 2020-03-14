#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include <optional>
#include "primitives/primitive.h"

class Intersection
{
private:
    // attributes
    double m_t;
    Primitive* m_object;

public:
    Intersection(double t, const Primitive *object);

    // accessor methods
    double get_t() const {return m_t;}
    Primitive* get_object() const {return m_object;}

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
    friend bool operator==(const Intersection &i1, const Intersection &i2);
};

// utility functions
Tuple normal(const Primitive *o, const Tuple &t);
std::vector<Intersection> intersect(const Primitive *o, const Ray &r);
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

#endif