#ifndef MESH_H
#define MESH_H

#include <cassert>
#include <fstream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "math/matrix.h"
#include "math/tuple.h"
#include "geometry/group.h"
#include "geometry/primitives/triangle.h"
#include "geometry/primitives/smooth_triangle.h"
#include "material/material.h"

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
    Mesh(const std::string &filepath, const math::Matrix4d &transformation = math::identity(), std::shared_ptr<material::Material> material = std::make_shared<material::ColorMaterial>(material::ColorMaterial{}));
};

} // namespace geometry

#endif
