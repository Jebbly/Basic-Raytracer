#include "image/framebuffer.h"

image::Framebuffer::Framebuffer(int width, int height) :
    m_width{width},
    m_height{height}
{
    init();
}

image::Framebuffer::~Framebuffer()
{
    (*m_resources)--;
    if (*m_resources == 0)
	destroy();
}

// initialize and destroy methods
void image::Framebuffer::init()
{
    m_buffer = new image::Color*[m_height];
    for (int i = 0; i < m_height; i++)
    {
	m_buffer[i] = new image::Color[m_width];
    }

    m_resources = new int;
    *m_resources = 1;
}

void image::Framebuffer::destroy()
{
    for (int i = 0; i < m_height; i++)
    {
	delete[] m_buffer[i];
    }
    delete[] m_buffer;

    delete m_resources;
}

// copy overloads
image::Framebuffer::Framebuffer(const Framebuffer &rhs) :
    m_width{rhs.m_width},
    m_height{rhs.m_height},
    m_buffer{rhs.m_buffer},
    m_resources{rhs.m_resources}
{
    (*m_resources)++;
}

image::Framebuffer& image::Framebuffer::operator=(const image::Framebuffer &rhs)
{
    if (&rhs == this)
	return *this;

    (*m_resources)--;
    if (*m_resources == 0)
	destroy();

    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_buffer = rhs.m_buffer;
    m_resources = rhs.m_resources;
    (*m_resources)++;

    return *this;
}

// utility functions
void image::Framebuffer::write_pixel(int x, int y, const image::Color &color)
{
    assert(x >= 0 && x < m_width &&
	   y >= 0 && y < m_height &&
	   "pixel outside of buffer");
    
    m_buffer[y][x] = color;
}

void image::Framebuffer::save_buffer(const std::string &name)
{
    std::ofstream output(name, std::ofstream::trunc);

    // standard P3 output
    output << "P3" << '\n' 
	   << m_width << ' ' << m_height << '\n' 
	   << 255 << '\n';
    for (int y = 0; y < m_height; y++)
    {
	for (int x = 0; x < m_width; x++)
	{
	    output << m_buffer[y][x];
	}
	output << '\n';
    }

    output.close();
}
