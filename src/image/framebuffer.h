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
    int get_width() const {return m_width;}
    int get_height() const {return m_height;}
    Tuple get_pixel(int x, int y) const;

    // utility functions
    void write_pixel(int x, int y, const Tuple &color);
    void save_buffer(const std::string &name);
};

#endif