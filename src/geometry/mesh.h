#ifndef MESH_H
#define MESH_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include "utility/constants.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "material/material.h"
#include "geometry/primitives/primitive.h"
#include "geometry/primitives/triangle.h"
#include "geometry/primitives/smooth_triangle.h"
#include "geometry/group.h"

namespace geometry
{

class Mesh : public Group
{
private:
    // attributes
    std::vector<math::Tuple4d> m_vertices;
    std::vector<math::Tuple4d> m_normals;
    std::vector<std::shared_ptr<primitive::Triangle>> m_triangles;
    bool m_smooth;

    // helper functions
    void flat_triangulate(const std::vector<int> &vertex_indices);
    void smooth_triangulate(const std::vector<int> &vertex_indices, const std::vector<int> &normal_indices);
    void parse_obj_file(const std::string &filepath);

public:
    Mesh(const std::string &filepath, const math::Matrix4d &transformation = math::identity<double, 4>(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));

    // accessor methods
    const std::vector<math::Tuple4d>& get_vertices() const;
    const std::vector<math::Tuple4d>& get_normals() const;
    const std::vector<std::shared_ptr<primitive::Triangle>>& get_triangles() const;
};

} // namespace geometry

#endif