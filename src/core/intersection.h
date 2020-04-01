#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include <optional>
#include <utility>
#include "primitives/primitive.h"

class Primitive;

class Intersection
{
private:
    // attributes
    double m_t;
    Primitive* m_object;
    std::pair<double, double> m_uv;

public:
    Intersection(double t, Primitive *object, std::pair<double, double> uv = std::make_pair(0, 0));

    // accessor methods
    double get_t() const;
    Primitive* get_object() const;
    const std::pair<double, double>& get_uv() const;

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
    friend bool operator==(const Intersection &i1, const Intersection &i2);
};

// utility function
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

#endif