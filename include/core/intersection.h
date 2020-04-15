#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <algorithm>
#include <optional>
#include <utility>
#include <vector>
#include "geometry/primitives/primitive.h"

namespace geometry::primitive {class Primitive;}

namespace core
{

class Intersection
{
private:
    // attributes
    double m_t;
    geometry::primitive::Primitive* m_object;
    std::pair<double, double> m_uv;

public:
    Intersection(double t, geometry::primitive::Primitive *object, std::pair<double, double> uv = std::make_pair(0, 0));

    // accessor methods
    inline double t() const {return m_t;}
    inline geometry::primitive::Primitive* object() const {return m_object;}
    inline const std::pair<double, double>& uv() const {return m_uv;}

    // comparison overloads
    friend bool operator<(const Intersection &i1, const Intersection &i2);
    friend bool operator==(const Intersection &i1, const Intersection &i2);
};

// utility function
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

} // namespace core

#endif
