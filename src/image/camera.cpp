#include "image/camera.h"

Camera::Camera(int width, int height, double FOV) :
    m_width{width},
    m_height{height},
    m_FOV{FOV},
    m_transformation{identity()}
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
double Camera::get_pixel_size() const
{
    return (m_half_width * 2) / m_width;
}

void Camera::set_transform(const Matrix &m)
{
    m_transformation = m;
}

// raytrace functions
Ray Camera::ray(int x, int y) const
{
    double pixel_size = get_pixel_size();
    double x_offset = (x + 0.5) * pixel_size;
    double y_offset = (y + 0.5) * pixel_size;

    double world_x = m_half_width - x_offset;
    double world_y = m_half_height - y_offset;

    Tuple pixel = multiply(m_transformation.inverse(), point(world_x, world_y, -1));
    Tuple origin = multiply(m_transformation.inverse(), point(0, 0, 0));
    Tuple direction = normalize(pixel - origin);

    return Ray{origin, direction};
}

Framebuffer Camera::render(const World &w) const
{
    Framebuffer ret{m_width, m_height};
    for (int y = 0; y < m_height; y++)
    {
	for (int x = 0; x < m_width; x++)
	{
	    Ray shoot_ray = ray(x, y);
	    Tuple color = w.final_color(shoot_ray);
	    ret.write_pixel(x, y, color);
	}
    }
    return ret;
}