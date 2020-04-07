#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "math/matrix.h"
#include "image/framebuffer.h"
#include "core/ray.h"
#include "scene/world.h"

namespace image
{

class Camera
{
private:
    // attributes
    int m_width, m_height;
    double m_FOV;
    math::Matrix4d m_transformation;
    double m_half_width, m_half_height;

public:
    Camera(int width, int height, double FOV);

    // accessor methods
    int get_height() const { return m_height; }
    int get_width() const { return m_width; }
    double get_FOV() const { return m_FOV; }
    double get_pixel_size() const;

    void set_transform(const math::Matrix4d &m);

    // raytrace functions
    Ray ray(int x, int y) const;
    Framebuffer render(const scene::World &w) const;
};

} // namespace image

#endif