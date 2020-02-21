#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include "primitives/sphere.h"

class Intersection
{
private:
    // attributes
    double m_t;
    Sphere m_object;
    bool m_valid;

public:
    Intersection();
    Intersection(double t, const Sphere &object);

    // accessor methods
    double t() const {return m_t;}
    const Sphere& object() const {return m_object;}
    bool valid() const {return m_valid;}

    // comparison overload
    friend bool operator<(const Intersection &i1, const Intersection &i2);
};

// utility functions
std::vector<Intersection> intersections(const Ray &r, const Sphere &object);
Intersection hit(const std::vector<Intersection> &intersections);

#endif