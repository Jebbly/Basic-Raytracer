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
    const Primitive* m_object;

public:
    Intersection(double t, const Primitive *object);

    // accessor methods
    double get_t() const {return m_t;}
    const Primitive* get_object() const {return m_object;}

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
};

// utility functions
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

#endif