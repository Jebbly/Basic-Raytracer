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
    Framebuffer(int width, int height);
    ~Framebuffer();

    // accessor methods
    int width() const {return m_width;}
    int height() const {return m_height;}

    // utility functions
    void write_pixel(int x, int y, const Tuple &color);
    void save_buffer(const std::string &name);
};

#endif