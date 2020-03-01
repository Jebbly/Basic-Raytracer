#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include <optional>
#include "primitives/sphere.h"

class Intersection
{
private:
    // attributes
    double m_t;
    Sphere m_object;

public:
    Intersection();
    Intersection(double t, const Sphere &object);

    // accessor methods
    double get_t() const {return m_t;}
    const Sphere& get_object() const {return m_object;}

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
};

// utility functions
std::vector<Intersection> intersections(const Ray &r, const Sphere &object);
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

#endif