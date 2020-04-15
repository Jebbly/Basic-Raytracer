#include "geometry/mesh.h"

geometry::Mesh::Mesh(const std::string &filepath, const math::Matrix4d &transformation, std::shared_ptr<material::Material> material) :
    Group{transformation, material},
    m_smooth{false}
{
    parse_obj_file(filepath);
   
    for (int i = 0; i < m_triangles.size(); i++)
    {
	m_triangles.at(i)->set_material(m_material);
	add_child((primitive::Primitive*) m_triangles.at(i).get());
    }
}

// helper functions
void geometry::Mesh::flat_triangulate(const std::vector<int> &vertex_indices)
{
    for (int i = 1; i < vertex_indices.size() - 1; i++)
    {
	m_triangles.push_back(std::make_shared<primitive::Triangle>(primitive::Triangle{m_vertices.at(vertex_indices.at(0) - 1),
											m_vertices.at(vertex_indices.at(i) - 1),
											m_vertices.at(vertex_indices.at(i + 1) - 1)}));
    }
}

void geometry::Mesh::smooth_triangulate(const std::vector<int> &vertex_indices, const std::vector<int> &normal_indices)
{
    for (int i = 1; i < vertex_indices.size() - 1; i++)
    {
	m_triangles.push_back(std::make_shared<primitive::SmoothTriangle>(primitive::SmoothTriangle{m_vertices.at(vertex_indices.at(0) - 1),
												    m_vertices.at(vertex_indices.at(i) - 1),
												    m_vertices.at(vertex_indices.at(i + 1) - 1),
												    m_normals.at(normal_indices.at(0) - 1),
												    m_normals.at(normal_indices.at(i) - 1),
												    m_normals.at(normal_indices.at(i + 1) - 1)}));
    }
}

void geometry::Mesh::parse_obj_file(const std::string &filepath)
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

	    math::Tuple4d vertex = math::point(x, y, z);
	    m_vertices.push_back(vertex);
	}
	else if (prefix == "vn")
	{
	    m_smooth = true;
	    std::istringstream vn{line.substr(2)};

	    double x, y, z;
	    vn >> x >> y >> z;

	    math::Tuple4d normal = math::vector(x, y, z);
	    m_normals.push_back(normal);
	}
	else if (prefix == "f ")
	{
	    if (m_smooth)
	    {
		// format data properly
		for (size_t i = 0; i < 3; i++)
		{
		    size_t pos = line.find('/');
		    size_t len = line.find('/', pos + 1) - pos;
		    line.replace(pos, len + 1, " ");
		}

		std::istringstream f{line.substr(2)};

		std::vector<int> vertex_indices, normal_indices;
		for (int i = 0; i < 3; i++)
		{
		    int vertex_index, normal_index;
		    f >> vertex_index >> normal_index;
		    vertex_indices.push_back(vertex_index);
		    normal_indices.push_back(normal_index);
		}

		smooth_triangulate(vertex_indices, normal_indices);
	    }
	    else
	    {
		std::istringstream f{line.substr(2)};

		std::vector<int> vertex_indices;
		std::copy(std::istream_iterator<int>(f), std::istream_iterator<int>(), std::back_inserter(vertex_indices));

		flat_triangulate(vertex_indices);
	    }
	}
    }

    input.close();
}

// accessor methods
const std::vector<math::Tuple4d>& geometry::Mesh::get_vertices() const
{
    return m_vertices;
}

const std::vector<math::Tuple4d>& geometry::Mesh::get_normals() const
{
    return m_normals;
}

const std::vector<std::shared_ptr<geometry::primitive::Triangle>>& geometry::Mesh::get_triangles() const
{
    return m_triangles;
}