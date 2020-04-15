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
image::Framebuffer::Framebuffer(const Framebuffer &fb) :
    m_width{fb.m_width},
    m_height{fb.m_height},
    m_buffer{fb.m_buffer},
    m_resources{fb.m_resources}
{
    (*m_resources)++;
}

image::Framebuffer& image::Framebuffer::operator=(const image::Framebuffer &fb)
{
    if (&fb == this)
	return *this;

    (*m_resources)--;
    if (*m_resources == 0)
	destroy();

    m_width = fb.m_width;
    m_height = fb.m_height;
    m_buffer = fb.m_buffer;
    m_resources = fb.m_resources;
    (*m_resources)++;

    return *this;
}

// accessor methods
image::Color image::Framebuffer::get_pixel(int x, int y) const
{
    assert(x >= 0 && x < get_width() &&
	   y >= 0 && y < get_height() &&
	   "index outside of buffer");

    return m_buffer[y][x];
}

// utility functions
void image::Framebuffer::write_pixel(int x, int y, const image::Color &color)
{
    assert(x >= 0 && x < get_width() &&
	   y >= 0 && y < get_height() &&
	   "pixel outside of buffer");
    
    m_buffer[y][x] = color;
}

void image::Framebuffer::save_buffer(const std::string &name)
{
    std::ofstream output(name, std::ofstream::trunc);

    // standard P3 output
    output << "P3" << '\n' 
	   << get_width() << ' ' << get_height() << '\n' 
	   << 255 << '\n';
    for (int y = 0; y < get_height(); y++)
    {
	for (int x = 0; x < get_width(); x++)
	{
	    output << m_buffer[y][x];
	}
	output << '\n';
    }

    output.close();
}