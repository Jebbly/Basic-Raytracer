#include "primitives/mesh.h"

Mesh::Mesh(const std::string &filepath, const Matrix &transformation, Material *material) :
    Group{transformation, material}
{
    parse_obj_file(filepath);
   
    for (int i = 0; i < m_triangles.size(); i++)
    {
	m_triangles.at(i).set_material(m_material);
	add_child((Primitive*) &(m_triangles.at(i)));
    }
}

// helper functions
void Mesh::triangulate(const std::vector<int> &vertex_indices)
{
    for (int i = 1; i < vertex_indices.size() - 1; i++)
    {
	m_triangles.push_back(Triangle{m_vertices.at(vertex_indices.at(0) - 1),
				       m_vertices.at(vertex_indices.at(i) - 1),
				       m_vertices.at(vertex_indices.at(i + 1) - 1)});
    }
}

void Mesh::parse_obj_file(const std::string &filepath)
{
    std::ifstream input(filepath.c_str(), std::ios::in);
    assert(input && "cannot open file");

    std::string line;
    while (std::getline(input, line))
    {
	std::string prefix = line.substr(0, 2);
	if (prefix == "v ")
	{
	    std::istringstream v{line.substr(2)};

	    double x, y, z;
	    v >> x >> y >> z;

	    Tuple vertex = point(x, y, z);
	    m_vertices.push_back(vertex);
	}
	else if (prefix == "f ")
	{
	    std::istringstream f{line.substr(2)};

	    std::vector<int> vertex_indices;
	    std::copy(std::istream_iterator<double>(f), std::istream_iterator<double>(), std::back_inserter(vertex_indices));

	    triangulate(vertex_indices);
	}
    }

    input.close();
}