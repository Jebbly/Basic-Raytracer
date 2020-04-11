#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <memory>
#include <vector>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "material/material.h"
#include "material/color_material.h"

namespace core {class Intersection;}
namespace geometry {class Group;}

namespace geometry::primitive
{

class Primitive
{
protected:
    // attributes
    math::Matrix4d m_transformation;
    std::shared_ptr<material::Material> m_material;
    Group *m_parent;

    // helper functions
    math::Tuple4d world_to_object(math::Tuple4d point) const;
    math::Tuple4d normal_to_world(math::Tuple4d normal) const;

public:
    Primitive(const math::Matrix4d &transformation = math::identity<double, 4>(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));

    // accessor methods
    const math::Matrix4d& get_transformation() const;
    std::shared_ptr<material::Material> get_material();
    const Group* get_parent() const;

    void set_transform(const math::Matrix4d &m);
    void set_material(std::shared_ptr<material::Material> m);
    void set_parent(Group *p);

    virtual bool includes(Primitive *p) const;

    // ray intersect functions
    math::Tuple4d normal(const math::Tuple4d &t, const core::Intersection &hit) const;
    std::vector<core::Intersection> intersect(const core::Ray &r);
    math::Tuple3d color(const math::Tuple4d &point) const;

    virtual std::vector<core::Intersection> local_intersect(const core::Ray &r) const = 0;
    virtual math::Tuple4d local_normal(const math::Tuple4d &t, const core::Intersection &hit) const = 0;

    // utility functions
    virtual void transform(const math::Matrix4d &transformation);
    core::BoundingBox bounds() const;
    virtual core::BoundingBox local_bounds() const = 0;
};

} // namespace geometry::primitive

#endif