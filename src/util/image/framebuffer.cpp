#include "util/image/framebuffer.h"

// utility functions
void Framebuffer::write_pixel(int x, int y, const Tuple &color)
{
    if (x >= 0 && x < m_width &&
	y >= 0 && y < m_height)
	m_buffer[y][x] = color;
}

void Framebuffer::save_buffer(const std::string name)
{
    std::ofstream output(name, std::ofstream::trunc);

    // standard P3 output
    output << "P3" << '\n' 
	   << m_width << ' ' << m_height << '\n' 
	   << 255 << '\n';
    for (int y = 0; y < m_height; y++)
    {
	for (int x = 0; x < m_width; x++)
	    output << m_buffer[y][x];
	output << '\n';
    }

    output.close();
}