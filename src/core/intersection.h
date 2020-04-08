#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <algorithm>
#include <optional>
#include <utility>
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
    double get_t() const;
    geometry::primitive::Primitive* get_object() const;
    const std::pair<double, double>& get_uv() const;

    // comparison overloads
    friend bool operator<(const Intersection &i1, const Intersection &i2);
    friend bool operator==(const Intersection &i1, const Intersection &i2);
};

// utility function
std::optional<const Intersection> hit(const std::vector<Intersection> &intersections);

} // namespace core

#endif