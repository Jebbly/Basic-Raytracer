#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <fstream>
#include <string>
#include "math/tuple.h"

class Framebuffer
{
private:
    int m_width, m_height;
    Tuple **m_buffer;

public:
    Framebuffer(int width, int height) :
	m_width{width},
	m_height{height}
    {
	m_buffer = new Tuple*[m_height];
	for (int i = 0; i < m_height; i++)
	    m_buffer[i] = new Tuple[m_width];
    }

    ~Framebuffer()
    {
	for (int i = 0; i < m_height; i++)
	    delete[] m_buffer[i];
	delete[] m_buffer;
    }

    // accessor methods
    int width() const {return m_width;}
    int height() const {return m_height;}

    // utility functions
    void write_pixel(int x, int y, const Tuple &color);
    void save_buffer(const std::string name);
};

#endif