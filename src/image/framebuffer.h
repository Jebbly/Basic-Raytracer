#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cassert>
#include <fstream>
#include <string>
#include "image/color.h"

namespace image
{

class Framebuffer
{
private:
    // attributes
    int m_width, m_height;
    image::Color **m_buffer;
    int *m_resources;

    // initialize and destroy methods
    void init();
    void destroy();

public:
    Framebuffer(int width, int height);
    ~Framebuffer();

    // copy overloads
    Framebuffer(const Framebuffer &rhs);
    Framebuffer& operator=(const Framebuffer &rhs);

    // utility functions
    void write_pixel(int x, int y, const image::Color &color);
    void save_buffer(const std::string &name);
};

} // namespace image

#endif
