#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "materials/material.h"
#include "materials/color_material.h"

class Intersection;

class Primitive
{
protected:
    // attributes
    Matrix m_transformation;
    Material* m_material;

public:
    Primitive(const Matrix &transformation = identity(), Material *material = &(ColorMaterial{}));

    // accessor methods
    const Matrix& get_transformation() const;
    const Material* get_material() const;

    void set_transform(const Matrix &m);
    void set_material(Material *m);

    // ray intersect functions
    Tuple normal(const Tuple &t) const;
    std::vector<Intersection> intersect(const Ray &r);
    Tuple color(const Tuple &point) const;

    virtual std::vector<double> local_intersect(const Ray &r) const = 0;
    virtual Tuple local_normal(const Tuple &t) const = 0;
};

#endif