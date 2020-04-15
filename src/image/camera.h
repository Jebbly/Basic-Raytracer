#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include "math/matrix.h"
#include "core/ray.h"
#include "image/color.h"
#include "image/framebuffer.h"
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

    // helper function
    double pixel_size() const;

public:
    Camera(int width, int height, double FOV);

    // accessor method
    void transform(const math::Matrix4d &transformation);

    // raytrace functions
    core::Ray ray(int x, int y) const;
    Framebuffer render(const scene::World &world) const;
};

} // namespace image

#endif
