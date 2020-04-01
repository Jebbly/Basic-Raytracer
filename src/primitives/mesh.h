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
#include "utility/common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "core/intersection.h"
#include "core/bounding_box.h"
#include "materials/material.h"
#include "primitives/primitive.h"
#include "primitives/triangle.h"
#include "primitives/smooth_triangle.h"
#include "primitives/group.h"

class Mesh : public Group
{
private:
    // attributes
    std::vector<Tuple> m_vertices;
    std::vector<Tuple> m_normals;
    std::vector<std::shared_ptr<Triangle>> m_triangles;
    bool m_smooth;

    // helper functions
    void flat_triangulate(const std::vector<int> &vertex_indices);
    void smooth_triangulate(const std::vector<int> &vertex_indices, const std::vector<int> &normal_indices);
    void parse_obj_file(const std::string &filepath);

public:
    Mesh(const std::string &filepath, const Matrix &transformation = identity(), std::shared_ptr<Material> material = std::make_shared<ColorMaterial>(ColorMaterial{}));
};

#endif