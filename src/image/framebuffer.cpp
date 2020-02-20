#include "image/framebuffer.h"

Framebuffer::Framebuffer(int width, int height) :
    m_width{width},
    m_height{height}
{
    m_buffer = new Tuple * [m_height];
    for (int i = 0; i < m_height; i++)
	m_buffer[i] = new Tuple[m_width];
}

Framebuffer::~Framebuffer()
{
    for (int i = 0; i < m_height; i++)
	delete[] m_buffer[i];
    delete[] m_buffer;
}

// utility functions
void Framebuffer::write_pixel(int x, int y, const Tuple &color)
{
    assert(x >= 0 && x < width() &&
	   y >= 0 && y < height() &&
	   "pixel outside of buffer");
    
    m_buffer[y][x] = color;
}

void Framebuffer::save_buffer(const std::string &name)
{
    std::ofstream output(name, std::ofstream::trunc);

    // standard P3 output
    output << "P3" << '\n' 
	   << width() << ' ' << height() << '\n' 
	   << 255 << '\n';
    for (int y = 0; y < height(); y++)
    {
	for (int x = 0; x < width(); x++)
	{
	    output << m_buffer[y][x];
	}
	output << '\n';
    }

    output.close();
}