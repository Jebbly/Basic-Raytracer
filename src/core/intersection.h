#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include <optional>
#include "primitives/primitive.h"

class Primitive;

class Intersection
{
private:
    // attributes
    double m_t;
    Primitive* m_object;

public:
    Intersection(double t, Primitive *object);

    // accessor methods
    double get_t() const;
    Primitive* get_object() const;

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
    friend bool operator==(const Intersection &i1, const Intersection &i2);
};

// utility function
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

#endif