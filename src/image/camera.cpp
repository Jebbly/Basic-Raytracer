#include "image/camera.h"

image::Camera::Camera(int width, int height, double FOV) :
    m_width{width},
    m_height{height},
    m_FOV{FOV},
    m_transformation{math::identity<double, 4>()}
{
    double half_view = tan(m_FOV / 2);

    double aspect_ratio = (double) m_width / m_height;
    if (aspect_ratio >= 1)
    {
	m_half_width = half_view;
	m_half_height = half_view / aspect_ratio;
    }
    else
    {
	m_half_width = half_view * aspect_ratio;
	m_half_height = half_view;
    }
}

// accessor methods
double image::Camera::get_pixel_size() const
{
    return (m_half_width * 2) / m_width;
}

void image::Camera::set_transform(const math::Matrix4d &m)
{
    m_transformation = m;
}

// raytrace functions
core::Ray image::Camera::ray(int x, int y) const
{
    double pixel_size = get_pixel_size();
    double x_offset = (x + 0.5) * pixel_size;
    double y_offset = (y + 0.5) * pixel_size;

    double world_x = m_half_width - x_offset;
    double world_y = m_half_height - y_offset;

    math::Tuple4d pixel = m_transformation.inverse() * math::point<double>(world_x, world_y, -1);
    math::Tuple4d origin = m_transformation.inverse() * math::point<double>(0, 0, 0);
    math::Tuple4d direction = (pixel - origin).normalize();

    return core::Ray{origin, direction};
}

image::Framebuffer image::Camera::render(const scene::World &w) const
{
    image::Framebuffer ret{m_width, m_height};
    for (int y = 0; y < m_height; y++)
    {
	for (int x = 0; x < m_width; x++)
	{
	    core::Ray shoot_ray = ray(x, y);
	    image::Color color = w.final_color(shoot_ray, 0);
	    ret.write_pixel(x, y, color);
	}
    }
    return ret;
}